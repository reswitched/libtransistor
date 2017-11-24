#include<libtransistor/context.h>

libtransistor_context_t *libtransistor_context;

void libtransistor_set_keep_loaded() {
	libtransistor_context->return_flags|= RETF_KEEP_LOADED;
}

void libtransistor_set_run_meminfo() {
	libtransistor_context->return_flags|= RETF_RUN_MEMINFO;
}

void libtransistor_set_close_browser() {
	libtransistor_context->return_flags|= RETF_CLOSE_BROWSER;
}
