/**
 * @file libtransistor/ld/elf.h
 * @brief ELF structures
 */

#pragma once

#include<libtransistor/types.h>
#include<assert.h>
#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

typedef struct {
	uint64_t r_offset;
	uint32_t r_reloc_type;
	uint32_t r_symbol;
} Elf64_Rel;

typedef struct {
	uint32_t st_name;
	uint8_t st_info;
	uint8_t st_other;
	uint16_t st_shndx;
	uint64_t st_value;
	uint64_t st_size;
} Elf64_Sym;

#define STN_UNDEF 0
#define SHN_UNDEF 0

static_assert(sizeof(Elf64_Rela) == 0x18, "Elf64_Rela size should be 0x18");

enum {
	DT_NULL = 0,
	DT_NEEDED = 1,
	DT_PLTRELSZ = 2,
	DT_PLTGOT = 3,
	DT_HASH = 4,
	DT_STRTAB = 5,
	DT_SYMTAB = 6,
	DT_RELA = 7,
	DT_RELASZ = 8,
	DT_RELAENT = 9,
	DT_STRSZ = 10,
	DT_SYMENT = 11,
	// 12-15
	DT_SYMBOLIC = 16,
	DT_REL = 17,
	DT_RELSZ = 18,
	DT_RELENT = 19,
	DT_PLTREL = 20,
	// 21-22
	DT_JMPREL = 23,
	// 24
	DT_INIT_ARRAY = 25,
	DT_FINI_ARRAY = 26,
	DT_INIT_ARRAYSZ = 27,
	DT_FINI_ARRAYSZ = 28,
	// 29
	DT_FLAGS = 30,
	DT_GNU_HASH = 0x6ffffef5,
	DT_RELACOUNT = 0x6ffffff9,
};

/**
 * @brief Finds the value of the given tag in a dynamic section
 * @returns RESULT_OK, LIBTRANSISTOR_ERR_TRNLD_DUPLICATE_DT_ENTRY, or LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY
 */
result_t elf_dynamic_find_value(Elf64_Dyn *dynamic, int64_t tag, uint64_t *value);

/**
 * @brief Finds the value of the given tag in the dynamic section, treated as an offset from a given base
 * @returns RESULT_OK, LIBTRANSISTOR_ERR_TRNLD_DUPLICATE_DT_ENTRY, or LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY
 */
result_t elf_dynamic_find_offset(Elf64_Dyn *dynamic, int64_t tag, void **value, void *base);

/**
 * @brief Hashes a string for lookup in the .hash table
 */
uint64_t elf_hash_string(const char *string);

#ifdef __cplusplus
}
#endif
