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
 * @param find_mod Module to use if not found in load path
 * @param find_name Name of symbol to find
 * @param def Output for definition of symbol
 * @param defining_module Output for module defining \def
 * Implemented in ld/resolve.c, searches for symbols in global modules
 * in the order they were loaded.
 */
result_t ld_resolve_load_symbol(module_t *find_mod, const char *find_name, Elf64_Sym **def, module_t **defining_module);

/**
 * @brief Finds the definition for the given symbol
 * @param find_mod Module to begin search with
 * @param find_name Name of symbol to find
 * @param def Output for definition of symbol
 * @param defining_module Output for module defining \def
 * Implemented in ld/resolve.c, searches for symbols in \ref find_mod's
 * dependencies, breadth-first.
 */
result_t ld_resolve_dependency_symbol(module_t *find_mod, const char *find_name, Elf64_Sym **def, module_t **defining_module);

#ifdef __cplusplus
}
#endif
