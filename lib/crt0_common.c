#include<libtransistor/context.h>
#include<libtransistor/util.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/bsd.h>
#include<libtransistor/fs/blobfd.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/fs/squashfs.h>
#include<libtransistor/fs/fs.h>

#include<sys/socket.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<setjmp.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

#include "default_squashfs_image.h"
#include "squashfs/squashfuse.h"

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

static void (**init_array)(void) = NULL;
static void (**fini_array)(void) = NULL;

static ssize_t init_array_size = -1;
static ssize_t fini_array_size = -1;

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
		case 4: // DT_HASH
			break;
		case 5: // DT_STRTAB
			break;
		case 6: // DT_SYMTAB
			break;
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
		case 10: // DT_STRSZ
			break;
		case 11: // DT_SYMENT
			break;
		case 16: // DT_SYMBOLIC
			break;
		case 25: // DT_INIT_ARRAY
			if(init_array != NULL) {
				return true;
			}
			init_array = (void (**)(void)) (aslr_base + dynamic->d_val);
			break;
		case 26: // DT_FINI_ARRAY
			if(fini_array != NULL) {
				return true;
			}
			fini_array = (void (**)(void)) (aslr_base + dynamic->d_val);
			break;
		case 27: // DT_INIT_ARRAYSZ
			if(init_array_size != -1) {
				return true;
			}
			init_array_size = dynamic->d_val;
			break;
		case 28: // DT_FINI_ARRAYSZ
			if(fini_array_size != -1) {
				return true;
			}
			fini_array_size = dynamic->d_val;
			break;
		case 30: // DT_FLAGS
			// TODO
			break;
		case 0x6ffffff9: // DT_RELACOUNT
			rela_count = dynamic->d_val;
			break;
		default:
			dbg_printf("unknown dynamic tag: %d\n", dynamic->d_tag);
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

#define DEFAULT_NOCONTEXT_HEAP_SIZE 0x4000000

static jmp_buf exit_jmpbuf;
static int exit_value;

// filesystem stuff
static blob_file sqfs_blob;
static sqfs fs;
static trn_inode_t root_inode;

void setup_fs() { // TODO: error handling
	size_t sqfs_size = ((uint8_t*) &_libtransistor_squashfs_image_end) - ((uint8_t*) &_libtransistor_squashfs_image); // TODO: not this
	int sqfs_img_fd = blobfd_create(&sqfs_blob, &_libtransistor_squashfs_image, sqfs_size);
	sqfs_err err = SQFS_OK;

	err = sqfs_init(&fs, sqfs_img_fd, 0);
	if(err != SQFS_OK) {
		printf("failed to open SquashFS image\n");
		return;
	}

	result_t r;
	if((r = trn_sqfs_open_root(&root_inode, &fs)) != RESULT_OK) {
		printf("failed to open SquashFS root\n");
		return;
	}

	if((r = trn_fs_set_root(&root_inode)) != RESULT_OK) {
		printf("failed to set SquashFS root\n");
		return;
	}
}

int _libtransistor_start(libtransistor_context_t *ctx, void *aslr_base) {
	if(relocate(aslr_base)) {
		return -4;
	}
	
	dbg_printf("aslr base: %p", aslr_base);
	dbg_printf("ctx: %p", ctx);

	char *argv_default[] = {"contextless", NULL};
	char **argv = argv_default;
	int argc = 1;
  
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
		memcpy(&libtransistor_context, ctx, ctx->size);
	} else {
		dbg_printf("no context");

		if(svcSetHeapSize(&libtransistor_context.mem_base, DEFAULT_NOCONTEXT_HEAP_SIZE) != RESULT_OK) {
			dbg_printf("failed to set heap size");
			return -5;
		}
		libtransistor_context.mem_size = DEFAULT_NOCONTEXT_HEAP_SIZE;
	}

	dbg_printf("init stdio");
	bsslog_stdout._write = bsslog_write;
	bsslog_stdout._flags = __SWR | __SNBF;
	bsslog_stdout._bf._base = (void*) 1;

	bool initialized_bsd = false;
	if(libtransistor_context.has_bsd && libtransistor_context.std_socket > 0) {
		dbg_printf("using socklog stdio");
		bsd_init(); // borrow bsd object from loader
		initialized_bsd = true;
		int fd = socket_from_bsd(libtransistor_context.std_socket);
		if (fd < 0) {
			dbg_printf("Error creating socket: %d", errno);
		} else {
			if (dup2(fd, STDIN_FILENO) < 0)
				dbg_printf("Error setting up stdin: %d", errno);
			if (dup2(fd, STDOUT_FILENO) < 0)
				dbg_printf("Error setting up stdout: %d", errno);
			if (dup2(fd, STDERR_FILENO) < 0)
				dbg_printf("Error setting up stderr: %d", errno);
		}
	} else {
		// TODO: Create a fake FD for bsslog
		dbg_printf("using bsslog stdout");
		printf("_"); // init stdout
		getchar(); // init stdin
		stdout = &bsslog_stdout;
		stderr = &bsslog_stdout;
	}
	dbg_printf("set up stdout");

	/*
	  Automatically initialize sm, since 99% of applications are going to be using it
	  and if they don't explicitly initialize it, each ipc module will initialize it,
	  use it, then immediately finalize it.
	 */
	result_t r;
	if((r = sm_init()) != RESULT_OK) {
		printf("failed to initialize sm: 0x%x\n", r);
		goto fail_bsd;
	}

	setup_fs();

	if(init_array != NULL) {
		if(init_array_size == -1) {
			return true;
		}
		for(size_t i = 0; i < init_array_size/sizeof(init_array[0]); i++) {
			init_array[i]();
		}
	}

	int ret;
	if (setjmp(exit_jmpbuf) == 0) {
		ret = main(argc, argv);
		exit(ret);
	} else {
		ret = exit_value;
	}

	if(fini_array != NULL) {
		if(fini_array_size == -1) {
			return true;
		}
		for(size_t i = 0; i < fini_array_size/sizeof(fini_array[0]); i++) {
			fini_array[i]();
		}
	}
	
fail_bsd:
	/*
	  at this point, bsd and sm have already been destructed, but just in case we
	  ever change the destruction logic...
	 */
	if(initialized_bsd) {
		bsd_finalize();
	}
	sm_finalize();
	
	// If we had a context, copy out parameters in there
	if (ctx != NULL)
		memcpy(ctx, &libtransistor_context, ctx->size);

	return ret;
}

void _exit(int ret) {
	exit_value = ret;
	longjmp(exit_jmpbuf, 1);
}
