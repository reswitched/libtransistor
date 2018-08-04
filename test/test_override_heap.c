#include<libtransistor/runtime_config.h>

#include<stdio.h>
#include<malloc.h>

uint8_t local_heap[6 * 1024 * 1024];

runconf_heap_mode_t _trn_runconf_heap_mode = _TRN_RUNCONF_HEAP_MODE_OVERRIDE;
void *_trn_runconf_heap_base = local_heap;
size_t _trn_runconf_heap_size = sizeof(local_heap);

int main(int argc, char *argv[]) {
	printf("local heap at %p\n", local_heap);
	uint8_t *buf = malloc(64);
	printf("allocated at %p\n", buf);
	if(buf >= local_heap && (size_t) (buf - local_heap) < sizeof(local_heap)) {
		printf("inside local heap\n");
		return 0;
	} else {
		printf("outside local heap\n");
		return 1;
	}
}
