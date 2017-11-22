#include<libtransistor/context.h>
#include<libtransistor/util.h>

#include<assert.h>

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

int _libtransistor_start(libtransistor_context_t *ctx, void *aslr_base) {
  if(relocate(aslr_base)) {
    return -4;
  }
  
  dbg_printf("aslr base: %p", aslr_base);
  dbg_printf("ctx: %p", ctx);

  char **argv = NULL;
  int argc = 0;

  libtransistor_context_t empty_context;
  memset(&empty_context, 0, sizeof(empty_context));
  
  if(ctx != NULL) {
    dbg_printf("found context");
    dbg_printf("  version: %d", ctx->version);
    dbg_printf("  size: 0x%x", ctx->size);

    if(ctx->version > LIBTRANSISTOR_CONTEXT_VERSION) {
      dbg_printf("unrecognized context version");
      return -2;
    }
    
    if(ctx->version >= 1) {
      dbg_printf("context version 1 fields...");
      ctx->log_buffer = log_buffer;
      ctx->log_length = &log_length;
    }

    if(ctx->version >= 2) {
      dbg_printf("context version 2 fields...");
      argv = ctx->argv;
      argc = (int) ctx->argc;
    }

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
  }

  return main(argc, argv);
}
