/**
 * @file libtransistor/collections/list.h
 * @brief Lists
 * Inspired by the concepts of the Linux kernel list API
 */

#pragma once

#include<stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct trn_list_head_t trn_list_head_t;
struct trn_list_head_t {
	trn_list_head_t *prev;
	trn_list_head_t *next;
};

#define TRN_LIST_HEAD_INITIALIZER {.prev = NULL, .next = NULL}

#define trn_list_entry(type, field, head) ((type*) (((void*) (head)) - offsetof(type, field)))

inline void trn_list_add_tail(trn_list_head_t *list, trn_list_head_t *item) {
	while(list->next != NULL) {
		list = list->next;
	}
	list->next = item;
	item->prev = list;
	item->next = NULL;
}

#define trn_list_foreach(list, i) for(trn_list_head_t *i = (list)->next; i != NULL; i = i->next)

#ifdef __cplusplus
}
#endif
