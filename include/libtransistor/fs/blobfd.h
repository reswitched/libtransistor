#pragma once

#include<stdio.h>

typedef struct {
	void *data;
	size_t size;
	off_t head;
} blob_file;

int blobfd_create(blob_file *data, void *blob, size_t size);
