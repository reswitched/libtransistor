#include <libtransistor/nx.h>
#include <libtransistor/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
#include "nro.h"
#include "sha256.h"
#include "memory.h"
#include "http.h"

#define NRR_SIZE	0x1000

int nro_load_count;
int nro_unload_fail;
int nro_loaded_count;

static loader_config_entry_t nro_config[64];
static void *nro_base;
static void *nro_load_base;

static char *nro_argv[NRO_MAX_ARGS+1];
static char nro_args[NRO_MAX_ARG_BUF];
static int nro_argc;
static char *nro_argoffs;

extern thread_h aceloader_main_thread_handle;

uint64_t nro_start()
{
	uint64_t (*entry)(loader_config_entry_t*, thread_h) = nro_base + 0x80;
	uint64_t ret;

	// generate memory block
	if(mem_make_block())
	{
		printf("- failed to map memory block\n");
		return -1;
	}

	printf("- writing NRO config\n");
	
	int ent_no = 0;
	nro_config[ent_no].key = LCONFIG_KEY_MAIN_THREAD_HANDLE;
	nro_config[ent_no].flags = LOADER_CONFIG_FLAG_RECOGNITION_MANDATORY;
	nro_config[ent_no].main_thread_handle.main_thread_handle = aceloader_main_thread_handle;
	ent_no++;

	nro_config[ent_no].key = LCONFIG_KEY_OVERRIDE_HEAP;
	nro_config[ent_no].flags = LOADER_CONFIG_FLAG_RECOGNITION_MANDATORY;
	nro_config[ent_no].override_heap.heap_base = map_base;
	nro_config[ent_no].override_heap.heap_size = map_size;
	ent_no++;

	nro_config[ent_no].key = LCONFIG_KEY_OVERRIDE_SERVICE;
	nro_config[ent_no].flags = 0;
	nro_config[ent_no].override_service.override.service_name = str2u64(bsd_get_socket_service_name());
	nro_config[ent_no].override_service.override.service_handle = bsd_get_socket_service_handle();
	ent_no++;

	nro_config[ent_no].key = LCONFIG_KEY_STDIO_SOCKETS;
	nro_config[ent_no].flags = 0;
	nro_config[ent_no].stdio_sockets.s_stdout = std_sck;
	nro_config[ent_no].stdio_sockets.s_stdin  = std_sck;
	nro_config[ent_no].stdio_sockets.s_stderr = std_sck;
	nro_config[ent_no].stdio_sockets.socket_service = bsd_get_socket_service();
	ent_no++;

	if(nro_argc) {
		nro_config[ent_no].key = LCONFIG_KEY_ARGV;
		nro_config[ent_no].flags = 0;
		nro_config[ent_no].argv.argc = nro_argc;
		nro_config[ent_no].argv.argv = nro_argv;
		ent_no++;
	}

	if(loader_config.applet_workaround_active) {
		nro_config[ent_no].key = LCONFIG_KEY_APPLET_WORKAROUND;
		nro_config[ent_no].flags = LOADER_CONFIG_FLAG_RECOGNITION_MANDATORY;
		// TODO: determine this ourselves?
		nro_config[ent_no].applet_workaround.aruid = loader_config.applet_workaround_aruid;
		ent_no++;
	}

	if(loader_config.has_applet_type) {
		nro_config[ent_no].key = LCONFIG_KEY_APPLET_TYPE;
		nro_config[ent_no].flags = 0;
		nro_config[ent_no].applet_type.applet_type = loader_config.applet_type;
		ent_no++;
	}
	
	nro_config[ent_no].key = LCONFIG_KEY_END_OF_LIST;
	nro_config[ent_no].flags = LOADER_CONFIG_FLAG_RECOGNITION_MANDATORY;
	ent_no++;
	
	// Backup and clean main thread TLS pointer
	void **tls_userspace_pointer = (void**)(get_tls() + 0x1F8);
	void *tls_backup = *tls_userspace_pointer;
	*(void**)(get_tls() + 0x1f8) = NULL;

	// run NRO
	ret = entry(nro_config, aceloader_main_thread_handle);

	// Restore TLS
	*tls_userspace_pointer = tls_backup;

	// release memory block
	if(mem_destroy_block())
	{
		printf("- PANIC: failed to unmap memory\n");
		exit_loader();
	}

	return ret;
}

result_t nro_load(void *load_base, int in_size)
{
	result_t r;
	SHA256_CTX ctx;
	uint64_t free_size = heap_size - (load_base - heap_base);
	int nro_size = *(uint32_t*)(load_base + 0x18);
	uint32_t bss_size = *(uint32_t*)(load_base + 0x38);
	uint32_t nro_id = *(uint32_t*)(load_base + 0x10);
	uint32_t *nrru32 = (uint32_t*)(load_base + nro_size + bss_size);

	if(in_size < 0x1000 || nro_id != NRO_MAGIC || nro_size != in_size || nro_size & 0xFFF)
	{
		printf("- NRO is invalid\n");
		return 1;
	}

	if(nro_size + bss_size + NRR_SIZE > free_size)
	{
		printf("- NRO (+bss) is too big\n");
		return 2;
	}

	printf("- NRO %iB (%iB) bss %iB\n", nro_size, in_size, bss_size);

	// prepare NRR
	nrru32[0] = 0x3052524E; // NRR0
	nrru32[(0x338 >> 2) + 0] = NRR_SIZE; // size
	nrru32[(0x340 >> 2) + 0] = 0x350; // hash offset
	nrru32[(0x340 >> 2) + 1] = 0x1; // hash count

	// get hash
	sha256_init(&ctx);
	sha256_update(&ctx, (uint8_t*)load_base, nro_size);
	sha256_final(&ctx, (uint8_t*)&nrru32[0xD4]); // hash

	// load NRR
	r = ro_load_nrr(nrru32, NRR_SIZE);
	if(r)
	{
		printf("- NRR load error 0x%06X\n", r);
		return r;
	}

	// clear bss
	memset(load_base + nro_size, 0, bss_size);

	// load NRO
	r = ro_load_nro(&nro_base, load_base, nro_size, load_base + nro_size, bss_size);
	if(r)
	{
		printf("- NRO load error 0x%06X\n", r);
		return r;
	}

	nro_load_count++;
	nro_loaded_count++;
	nro_load_base = load_base;
	printf("- NRO base at 0x%016lX\n", (uint64_t)nro_base);

	// unload NRR
	r = ro_unload_nrr(nrru32);
	if(r)
	{
		printf("- NRR unload error 0x%06X\n", r);
		return r;
	}

	return 0;
}

result_t nro_unload()
{
	result_t r = 0;

	// unload NRO
	r = ro_unload_nro(nro_base, nro_load_base);
	if(r) {
		nro_unload_fail++;
		printf("- NRO unload error 0x%06X\n", r);
	} else {
		nro_loaded_count--;
	}

	// rescan for free heap block now
	if(mem_get_heap())
	{
		printf("- PANIC: failed get memory\n");
		exit_loader();
	}

	return r;
}

uint64_t nro_execute(void *load_base, int in_size)
{
	uint64_t ret;
	result_t r;

	r = nro_load(load_base, in_size);
	if(r)
		return r;

	ret = nro_start();

	nro_unload(); // unload can fail; for now not a critical error

	return ret;
}

void nro_arg_name(const char *text)
{
	// reset arg pointers
	nro_argc = 0;
	nro_argoffs = nro_args;
	// add argv[0]
	nro_add_arg(text);
}

void nro_add_arg(const char *text)
{
	if(nro_argc == NRO_MAX_ARGS)
		return;
	// copy text
	strcpy(nro_argoffs, text);
	// mark offset
	nro_argv[nro_argc] = nro_argoffs;
	// move pointer
	nro_argoffs += strlen(text)+1;
	// advance argc
	nro_argc++;
	// NULL next one
	nro_argv[nro_argc] = NULL;
}

void nro_print_args()
{
	for(int i = 0; i < nro_argc; i++) {
		if(i > 0) {
			printf(" ");
		}
		printf("%s", nro_argv[i]);
	}
}
