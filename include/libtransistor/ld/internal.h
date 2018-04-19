/**
 * @file libtransistor/ld/internal.h
 * @brief Implementation details for dynamic linker
 */

#pragma once

#include<libtransistor/collections/list.h>
#include<libtransistor/ld/ld.h>
#include<libtransistor/ld/elf.h>
#include<libtransistor/ld/module.h>

#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern trn_list_head_t ld_module_list_head;

typedef struct {
	uint32_t magic, dynamic_off, bss_start_off, bss_end_off;
	uint32_t unwind_start_off, unwind_end_off, module_object_off;
} module_header_t; // Nintendo's MOD0 struct

/**
 * @brief Finds the definition for the given symbol
 * Implemented in ld/resolve.c
 */
result_t ld_resolve_symbol(Elf64_Sym *find, module_t *find_module, Elf64_Sym **def, module_t **defining_module);

#ifdef __cplusplus
}
#endif
