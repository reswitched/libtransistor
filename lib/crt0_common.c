#include<libtransistor/context.h>
#include<libtransistor/util.h>

int main(libtransistor_context_t *ctx);

// from util.c
extern size_t log_length;
extern char log_buffer[0x20000];

int _libtransistor_start(libtransistor_context_t *ctx, void *aslr_base) {
  dbg_printf("aslr base: %p", aslr_base);
  dbg_printf("ctx: %p", ctx);
  if(ctx != NULL) {
    dbg_printf("found context");
    dbg_printf("  version: %d", ctx->version);
    dbg_printf("  size: 0x%x", ctx->size);
    if(ctx->version != LIBTRANSISTOR_CONTEXT_VERSION) {
      return -2;
    }
    if(ctx->size != sizeof(libtransistor_context_t)) {
      return -3;
    }
    dbg_printf("filling out context...");
    ctx->log_buffer = log_buffer;
    ctx->log_length = &log_length;
  } else {
    dbg_printf("no context");
  }
  return main(ctx);
}
