#include<libtransistor/nx.h>

#include<stdio.h>
#include<math.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

static const int sample_rate = 48000;
static const int chunk_rate = 10;
static const int num_frames_per_chunk = sample_rate / chunk_rate;

typedef struct {
	uint16_t l;
	uint16_t r;
} frame_t;

static const int num_channels = 2;

static const size_t chunk_size = ((num_frames_per_chunk * sizeof(frame_t)) + 0xfff) & ~0xfff;

// don't think this can be in mapped memory, since samples get DMA'd out of it
static frame_t __attribute__((aligned(0x1000))) chunks[2][chunk_size / sizeof(frame_t)];

static const int playback_seconds = 12;
static const int notes[] = {
	76, 75,
	76, 75, 76, 71, 74, 72,
	69, 69, 69, 60, 64, 69,
	71, 71, 71, 64, 68, 71,
	72, 72, 72, 64, 76, 75,
	76, 75, 76, 71, 74, 72,
	69, 69, 69, 60, 64, 69,
	71, 71, 71, 64, 72, 71,
	69, 69, 69, 69};
static const int num_notes = sizeof(notes)/sizeof(notes[0]);

double note_to_frequency(int note) {
	return pow(2, (note-69) / 12.0) * 440.0;
}

typedef struct {
	int last_note;
	int last_note_begin;

	// all in milliseconds
	int attack;
	int decay;
	int16_t sustain;
} adsr_t;

int16_t sine_wave(int frame_no, double frequency) {
	double wavelength = sample_rate / frequency;
	return (int16_t) (sin((frame_no * 2.0 * M_PI) / wavelength) * 0xFFF);
}

int16_t synth(int frame_no, adsr_t *adsr, int note, int channel) {
	if(adsr->last_note != note) {
		adsr->last_note_begin = frame_no;
		adsr->last_note = note;
	}

	const double frequency = note_to_frequency(note) / pow(2, channel+1);
	const int attack_samples = adsr->attack * (sample_rate / 1000);
	const int decay_samples = adsr->decay * (sample_rate / 1000);
	const int t = frame_no - adsr->last_note_begin;

	int16_t amplitude = adsr->sustain;
	
	if(t < attack_samples) {
		amplitude = ((0xFFF * t) / attack_samples);
	} else if(t < attack_samples + decay_samples) {
		amplitude = 0xFFF - (((0xFFF - adsr->sustain) * (t - attack_samples)) / decay_samples);
	}

	return ((uint32_t) sine_wave(frame_no, frequency) * amplitude) / 0xFFF;
}

// returns number of frames rendered
int render_frames(frame_t *buffer, int num_frames) {
	static int total_frames = 0;
	static adsr_t adsr = {
		0, 0, 30, (playback_seconds * 1000 / num_notes) - 30, 0
	};

	if(total_frames + num_frames > playback_seconds * sample_rate) {
		num_frames = (playback_seconds * sample_rate) - total_frames;
	}
	
	for(int i = 0; i < num_frames; i++) {
		const int note = notes[total_frames * num_notes / 48000 / playback_seconds];
		buffer[i].l = synth(total_frames, &adsr, note, 0);
		buffer[i].r = synth(total_frames, &adsr, note, 1);
		total_frames++;
	}

	return num_frames;
}

int main() {
	svcSleepThread(100000000);
  
	result_t r;
	ASSERT_OK(fail, sm_init());
	ASSERT_OK(fail_sm, audio_ipc_init());

	char names[8][0x20];
	uint32_t num_names;
	ASSERT_OK(fail_audio_ipc, audio_ipc_list_outputs(&names[0], 8, &num_names));
	if(num_names != 1) {
		printf("got back more than one AudioOut\n");
		hexdump(names, sizeof(names));
		goto fail_audio_ipc;
	}

	audio_output_t output;
	ASSERT_OK(fail_audio_ipc, audio_ipc_open_output(names[0], &output));

	if(output.sample_rate != sample_rate) {
		printf("expected sample rate of %d, got sample rate of %d\n", sample_rate, output.sample_rate);
		goto fail_audio_output;
	}

	if(output.num_channels != num_channels) {
		printf("expected %d channels, got %d\n", num_channels, output.num_channels);
		goto fail_audio_output;
	}

	if(output.sample_format != PCM_INT16) {
		printf("expected PCM_INT16, got %d\n", output.sample_format);
		goto fail_audio_output;
	}

	handle_t event;
	ASSERT_OK(fail_audio_output, audio_ipc_output_register_buffer_event(&output, &event));
	
	audio_output_buffer_t buffers[2];
	for(int i = 0; i < 2; i++) {
		buffers[i].ptr = &buffers[i].sample_data;
		buffers[i].sample_data = chunks[i];
		buffers[i].buffer_size = sizeof(chunks[i]);
		buffers[i].data_size = num_frames_per_chunk * sizeof(frame_t);
		buffers[i].unknown = 0;

		render_frames(buffers[i].sample_data, num_frames_per_chunk);

		ASSERT_OK(fail_audio_output, audio_ipc_output_append_buffer(&output, &buffers[i]));
	}

	ASSERT_OK(fail_audio_output, audio_ipc_output_start(&output));
	
	uint64_t t = svcGetSystemTick();
	while(svcGetSystemTick() - t < 19200000 * (uint64_t) playback_seconds) {
		uint32_t handle_idx;
		r = svcWaitSynchronization(&handle_idx, &event, 1, 33333333);
		if(r != RESULT_OK) {
			continue;
		}
		svcResetSignal(event);

		audio_output_buffer_t *released;
		
		uint32_t num;
		result_t r;
		while((r = audio_ipc_output_get_released_buffer(&output, &num, &released)) == RESULT_OK && released != NULL) {
			released->data_size = render_frames(released->sample_data, num_frames_per_chunk) * sizeof(frame_t);

			ASSERT_OK(fail_audio_output, audio_ipc_output_append_buffer(&output, released));
		}
		ASSERT_OK(fail_audio_output, r);
	}

	ASSERT_OK(fail_audio_output, audio_ipc_output_stop(&output));
	
	audio_ipc_output_close(&output);
	audio_ipc_finalize();
	sm_finalize();
	return 0;

fail_audio_output:
	audio_ipc_output_close(&output);
fail_audio_ipc:
	audio_ipc_finalize();
fail_sm:
	sm_finalize();
fail:
	return 1;
}
