#include<libtransistor/ld/loaders.h>
#include<libtransistor/ld/elf.h>

#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/address_space.h>
#include<libtransistor/loader_config.h>
#include<libtransistor/svc.h>

#include<libtransistor/ld/ld.h>

#include<string.h>
#include<stdlib.h>

typedef struct {
	Elf64_Phdr phdr;
	void *dst;
	void *src;
	void *clone;
	size_t size;
} ld_elf_segment_t;

typedef struct {
	void *as_base;
	size_t as_size;
	ld_elf_segment_t *segments;
	size_t num_segments;
} ld_elf_data_t;

static const uint8_t required_syscalls[] = {
	SVC_ID_SET_PROCESS_MEMORY_PERMISSION,
	SVC_ID_MAP_PROCESS_CODE_MEMORY,
	SVC_ID_UNMAP_PROCESS_CODE_MEMORY,
	0
};

static result_t ld_elf_can_load(void *file, size_t file_size) {
	if(!loader_config.has_process_handle) {
		dbg_printf("rejecting because no process handle");
		return LIBTRANSISTOR_ERR_TRNLD_NEEDS_PROCESS_HANDLE;
	}
	result_t r;
	if((r = lconfig_has_syscalls(required_syscalls)) != RESULT_OK) {
		return r;
	}

	// check header
	if(file_size < sizeof(Elf64_Ehdr)) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_ELF;
	}
	
	Elf64_Ehdr *ehdr = (Elf64_Ehdr*) file;
	uint8_t magic[4] = {0x7f, 'E', 'L', 'F'};
	if(memcmp(ehdr->e_ident, magic, 4) != 0) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_ELF;
	}
	if(ehdr->e_ident[EI_CLASS] != 2) { // check for 64-bit
		return LIBTRANSISTOR_ERR_TRNLD_UNSUPPORTED_ELF;
	}
	if(ehdr->e_ident[EI_DATA] != 1) { // check for little-endian
		return LIBTRANSISTOR_ERR_TRNLD_UNSUPPORTED_ELF;
	}
	if(ehdr->e_ident[EI_VERSION] != 1) { // check for version 1
		return LIBTRANSISTOR_ERR_TRNLD_UNSUPPORTED_ELF;
	}
	if(ehdr->e_machine != 0xb7) { // check for AArch64
		return LIBTRANSISTOR_ERR_TRNLD_UNSUPPORTED_ELF;
	}
	if(ehdr->e_version != 1) { // check for version 1
		return LIBTRANSISTOR_ERR_TRNLD_UNSUPPORTED_ELF;
	}
	if(ehdr->e_phentsize != sizeof(Elf64_Phdr)) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_ELF;
	}
	
	return RESULT_OK;
}

static result_t ld_elf_load(module_input_t *spec_out, void *file, size_t file_size) {
	result_t r;
	if((r = ld_elf_can_load(file, file_size)) != RESULT_OK) {
		return r;
	}

	ld_elf_data_t *data = malloc(sizeof(*data));
	if(data == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	data->num_segments = 0;
	
	Elf64_Ehdr *ehdr = (Elf64_Ehdr*) file;
	Elf64_Phdr *phdrs = file + ehdr->e_phoff;
	if(ehdr->e_phoff + sizeof(Elf64_Phdr) * ehdr->e_phnum > file_size) {
		return LIBTRANSISTOR_ERR_TRNLD_MALFORMED_ELF;
	}
	uint64_t total_as_size = 0;
	for(int i = 0; i < ehdr->e_phnum; i++) {
		Elf64_Phdr *phdr = &phdrs[i];
		if(phdr->p_type == PT_LOAD && phdr->p_memsz > 0) {
			data->num_segments++;
			if(phdr->p_vaddr + phdr->p_memsz > total_as_size) {
				total_as_size = phdr->p_vaddr + phdr->p_memsz;
			}
		}
	}

	data->segments = malloc(sizeof(*data->segments) * data->num_segments);
	if(data->segments == NULL) {
		r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		goto fail_data;
	}
	
	void *slide = as_reserve(total_as_size);
	data->as_base = slide;
	data->as_size = total_as_size;
	
	for(int i = 0, j = 0; i < ehdr->e_phnum; i++) {
		Elf64_Phdr *phdr = &phdrs[i];
		if(phdr->p_type == PT_LOAD && phdr->p_memsz > 0) {
			ld_elf_segment_t *seg = &data->segments[j++];
			seg->phdr = *phdr;
			seg->size = phdr->p_memsz;
			seg->dst = slide + phdr->p_vaddr;
			seg->src = file + phdr->p_offset;

			if(phdr->p_offset + phdr->p_filesz > file_size) {
				for(int k = 0; k < j-1; k++) {
					if(data->segments[k].clone) {
						free_pages(data->segments[k].clone);
					}
				}
				r = LIBTRANSISTOR_ERR_TRNLD_MALFORMED_ELF;
				goto fail_as;
			}
			
			if(phdr->p_filesz == phdr->p_memsz && (phdr->p_memsz & 0xFFF) == 0 && (phdr->p_offset & 0xFFF) == 0) {
				seg->clone = NULL;
			} else {
				seg->size = (phdr->p_memsz + 0xFFF) & ~0xFFF;
				seg->clone = alloc_pages(seg->size, seg->size, NULL);
				if(seg->clone == NULL) {
					for(int k = 0; k < j-1; k++) {
						if(data->segments[k].clone) {
							free_pages(data->segments[k].clone);
						}
					}
					r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
					goto fail_as;
				}
				memset(seg->clone + phdr->p_filesz, 0, seg->size - phdr->p_filesz);
				memcpy(seg->clone, seg->src, phdr->p_filesz);
				seg->src = seg->clone;
			}
		}
	}

	for(uint64_t i = 0; i < data->num_segments; i++) {
		ld_elf_segment_t *seg = &data->segments[i];
		if((r = svcMapProcessCodeMemory(loader_config.process_handle, seg->dst, seg->src, seg->size)) != RESULT_OK) {
			for(uint64_t j = 0; j < i; j++) {
				svcUnmapProcessCodeMemory(loader_config.process_handle, seg->dst, seg->src, seg->size);
			}
			goto fail_segment_clones;
		}

		uint32_t permissions = 0;
		if(seg->phdr.p_flags & PF_X) { permissions |= 4; }
		if(seg->phdr.p_flags & PF_W) { permissions |= 2; }
		if(seg->phdr.p_flags & PF_R) { permissions |= 1; }

		if((r = svcSetProcessMemoryPermission(loader_config.process_handle, (uint64_t) seg->dst, seg->size, permissions)) != RESULT_OK) {
			for(uint64_t j = 0; j <= i; j++) {
				svcUnmapProcessCodeMemory(loader_config.process_handle, seg->dst, seg->src, seg->size);
			}
			goto fail_segment_clones;
		}
	}

	
	spec_out->base = slide;
	spec_out->loader = &ld_loader_elf;
	spec_out->loader_data = data;
	return RESULT_OK;

fail_segment_clones:
	for(uint64_t i = 0; i < data->num_segments; i++) {
		if(data->segments[i].clone) {
			free_pages(data->segments[i].clone);
		}
	}
fail_as:
	as_release(slide, total_as_size);
	free(data->segments);
fail_data:
	free(data);
	return r;
}

static result_t result_or(result_t a, result_t b) {
	if(a != RESULT_OK) {
		return a;
	} else {
		return b;
	}
}

static result_t ld_elf_unload(module_input_t *spec) {
	result_t r = RESULT_OK;
	ld_elf_data_t *data = spec->loader_data;
	for(uint64_t i = 0; i < data->num_segments; i++) {
		ld_elf_segment_t *seg = &data->segments[i];
		r = result_or(r, svcUnmapProcessCodeMemory(loader_config.process_handle, seg->dst, seg->src, seg->size));
		if(seg->clone) {
			free_pages(seg->clone);
		}
	}

	as_release(data->as_base, data->as_size);
	free(data->segments);
	free(data);
	return r;
}

ld_loader_t ld_loader_elf = {
	.can_load = ld_elf_can_load,
	.load = ld_elf_load,
	.unload = ld_elf_unload,
};
