/**
 * @file libtransistor/fs/blobfd.h
 * @brief Memory-backed file functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>

typedef struct {
	void *data;
	size_t size;
	off_t head;
} blob_file;

int blobfd_create(blob_file *data, void *blob, size_t size);

#ifdef __cplusplus
}
#endif
