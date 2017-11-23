#include<libtransistor/context.h>
#include<libtransistor/util.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc/bsd.h>

#include<assert.h>
#include<stdio.h>
#include<string.h>

#include<ssp/ssp.h>

int main(int argc, char **argv);

// from util.c
extern size_t log_length;
extern char log_buffer[0x20000];

typedef struct {
  uint32_t magic, dynamic_off, bss_start_off, bss_end_off;
  uint32_t unwind_start_off, unwind_end_off, module_object_off;
} module_header_t;

typedef struct {
  int64_t d_tag;
  union {
    uint64_t d_val;
    void *d_ptr;
  };
} Elf64_Dyn;

typedef struct {
	uint64_t r_offset;
	uint32_t r_reloc_type;
	uint32_t r_symbol;
	uint64_t r_addend;
} Elf64_Rela;

static_assert(sizeof(Elf64_Rela) == 0x18, "Elf64_Rela size should be 0x18");

// defined in crt0.nxo.S, mostly to avoid using the GOT before we relocate its entries
extern module_header_t *_get_module_header();

static bool relocate(uint8_t *aslr_base) {
  module_header_t *mod_header = _get_module_header();
  Elf64_Dyn *dynamic = (Elf64_Dyn*) (((uint8_t*) mod_header) + mod_header->dynamic_off);
  uint64_t rela_offset = 0;
  uint64_t rela_size = 0;
  uint64_t rela_ent = 0;
  uint64_t rela_count = 0;
  bool found_rela = false;
  
  while(dynamic->d_tag > 0) {
    switch(dynamic->d_tag) {
    case 7: // DT_RELA
      if(found_rela) {
        return true;
      }
      rela_offset = dynamic->d_val;
      found_rela = true;
      break;
    case 8: // DT_RELASZ
      rela_size = dynamic->d_val;
      break;
    case 9: // DT_RELAENT
      rela_ent = dynamic->d_val;
      break;
    case 16: // DT_SYMBOLIC
      break;
    case 0x6ffffff9: // DT_RELACOUNT
      rela_count = dynamic->d_val;
      break;
    }
    dynamic++;
  }
  
  if(rela_ent != 0x18) {
    return true;
  }
  
  if(rela_size != rela_count * rela_ent) {
    return true;
  }
  
  Elf64_Rela *rela_base = (Elf64_Rela*) (aslr_base + rela_offset);
  for(uint64_t i = 0; i < rela_count; i++) {
    Elf64_Rela rela = rela_base[i];
    
    switch(rela.r_reloc_type) {
    case 0x403: // R_AARCH64_RELATIVE
      if(rela.r_symbol != 0) {
        return true;
      }
      *(void**)(aslr_base + rela.r_offset) = aslr_base + rela.r_addend;
      break;
    default:
      return true;
    }
  }

  return false;
}

static FILE bsslog_stdout;
static int bsslog_write(struct _reent *reent, void *v, const char *ptr, int len) {
  log_string(ptr, len);
  return len;
}

static FILE socklog_stdout;
static int socklog_write(struct _reent *reent, void *v, const char *ptr, int len) {
  return bsd_send(libtransistor_context->std_socket, ptr, len, 0);
}

// dummy for linker fail
void *__trunctfdf2() {
  return NULL;
}
// dummy for linker fail
long double __extenddftf2(double a) {
  return (long double) a;
}

#define DEFAULT_NOCONTEXT_HEAP_SIZE 0x400000

static bool dont_finalize_bsd = false;

int _libtransistor_start(libtransistor_context_t *ctx, void *aslr_base) {
  if(relocate(aslr_base)) {
    return -4;
  }
  
  __guard_setup();

  dbg_printf("aslr base: %p", aslr_base);
  dbg_printf("ctx: %p", ctx);

  char **argv = NULL;
  int argc = 0;

  libtransistor_context_t empty_context;
  memset(&empty_context, 0, sizeof(empty_context));
  
  if(ctx != NULL) {
    dbg_printf("found context");
    dbg_printf("  magic: 0x%x", ctx->magic);
    dbg_printf("  version: %d", ctx->version);
    dbg_printf("  size: 0x%x", ctx->size);

    if(ctx->magic != LIBTRANSISTOR_CONTEXT_MAGIC) {
      dbg_printf("invalid context magic");
      return -2;
    }
    
    ctx->log_buffer = log_buffer;
    ctx->log_length = &log_length;
    ctx->return_flags = 0;
    
    argv = ctx->argv;
    argc = (int) ctx->argc;

    if(ctx->version != LIBTRANSISTOR_CONTEXT_VERSION) {
      dbg_printf("mismatched context version");
      return -2;
    }
    
    if(ctx->size != sizeof(libtransistor_context_t)) {
      dbg_printf("mismatched context size");
      return -3;
    }

    libtransistor_context = ctx;
  } else {
    dbg_printf("no context");

    libtransistor_context = &empty_context;
    if(svcSetHeapSize(&libtransistor_context->mem_base, DEFAULT_NOCONTEXT_HEAP_SIZE) != RESULT_OK) {
      dbg_printf("failed to set heap size");
      return -5;
    }
    libtransistor_context->mem_size = DEFAULT_NOCONTEXT_HEAP_SIZE;
  }

  dbg_printf("init stdout");
  bsslog_stdout._write = bsslog_write;
  bsslog_stdout._flags = __SWR | __SNBF;
  bsslog_stdout._bf._base = (void*) 1;

  socklog_stdout._write = socklog_write;
  socklog_stdout._flags = __SWR | __SNBF;
  socklog_stdout._bf._base = (void*) 1;

  printf("_"); // init stdout
  if(libtransistor_context->has_bsd && libtransistor_context->std_socket > 0) {
    dbg_printf("using socklog stdout");
    bsd_init(); // borrow bsd object from loader
    stdout = &socklog_stdout;
    stderr = &socklog_stdout;
  } else {
    dbg_printf("using bsslog stdout");
    stdout = &bsslog_stdout;
    stderr = &bsslog_stdout;
  }
  dbg_printf("set up stdout");
  
  int ret = main(argc, argv);

  if(libtransistor_context->has_bsd && libtransistor_context->std_socket > 0 && !dont_finalize_bsd) {
    bsd_finalize();
  }

  return ret;
}

void libtransistor_dont_finalize_bsd() {
  dont_finalize_bsd = true;
}
