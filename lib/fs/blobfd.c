#include<libtransistor/fs/blobfd.h>
#include<libtransistor/fd.h>
#include<libtransistor/err.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>

static result_t blobfd_seek(void *vfile, off_t offset, int whence, off_t *position) {
	blob_file *file = vfile;
	switch(whence) {
	case SEEK_SET:
		file->head = offset;
		break;
	case SEEK_CUR:
		file->head+= offset;
		break;
	case SEEK_END:
		file->head = file->size + offset;
		break;
	default:
		return LIBTRANSISTOR_ERR_INVALID_ARGUMENT;
	}
	*position = file->head;
	return RESULT_OK;
}

static result_t blobfd_read(void *vfile, char *buffer, size_t size, size_t *bytes_read) {
	blob_file *file = vfile;
	size_t sz = size;
	if(file->head + sz > file->size) {
		sz = file->size - file->head;
	}
	memcpy(buffer, file->data + file->head, sz);
	file->head+= sz;
	*bytes_read = sz;
	return RESULT_OK;
}

static result_t blobfd_write(void *vfile, const char *buffer, size_t size, size_t *bytes_written) {
	return LIBTRANSISTOR_ERR_FS_READ_ONLY;
}

static result_t blobfd_release(trn_file_t *f) {
	return RESULT_OK;
}

static trn_file_ops_t blobfd_ops = {
	.seek = blobfd_seek,
	.read = blobfd_read,
	.write = blobfd_write,
	.release = blobfd_release
};

int blobfd_create(blob_file *file, void *blob, size_t size) {
	file->data = blob;
	file->size = size;
	file->head = 0;
	return fd_create_file(&blobfd_ops, file);
}
