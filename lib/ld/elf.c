#include<libtransistor/ld/elf.h>
#include<libtransistor/err.h>
#include<stdint.h>

result_t elf_dynamic_find_value(Elf64_Dyn *dynamic, int64_t tag, uint64_t *value) {
	uint64_t *found = NULL;
	*value = 0;
	for(; dynamic->d_tag != DT_NULL; dynamic++) {
		if(dynamic->d_tag == tag) {
			if(found != NULL) {
				return LIBTRANSISTOR_ERR_TRNLD_DUPLICATE_DT_ENTRY;
			} else {
				found = &dynamic->d_val;
			}
		}
	}
	if(found == NULL) {
		return LIBTRANSISTOR_ERR_TRNLD_MISSING_DT_ENTRY;
	}
	*value = *found;
	return RESULT_OK;
}

result_t elf_dynamic_find_offset(Elf64_Dyn *dynamic, int64_t tag, void **value, void *aslr_base) {
	uint64_t intermediate;
	result_t r = elf_dynamic_find_value(dynamic, tag, &intermediate);
	*value = aslr_base + intermediate;
	return r;
}

uint64_t elf_hash_string(const char *name) {
	uint64_t h = 0;
	uint64_t g;
	while(*name) {
		h = (h << 4) + *(const uint8_t*) name++;
		if((g = (h & 0xf0000000)) != 0) {
			h ^= g >> 24;
		}
		h&= ~g;
	}
	return h;
}
