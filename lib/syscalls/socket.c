#include<libtransistor/nx.h>
#include<libtransistor/fd.h>

#include<sys/socket.h>
#include<stdlib.h>
#include<errno.h>

static struct file_operations socket_fops;

int socket_from_bsd(int bsd_fd) {
	int *bsd_fd_mem = malloc(sizeof(int));
	if (bsd_fd_mem == NULL) {
		errno = ENOMEM;
		return -1;
	}
	*bsd_fd_mem = bsd_fd;
	int fd = fd_create_file(&socket_fops, bsd_fd_mem);
	if (fd < 0) {
		free(bsd_fd_mem);
		errno = fd;
		return -1;
	}
	return fd;
}

int socket(int domain, int type, int protocol) {
	bsd_init();
	int bsd_fd = bsd_socket(domain, type, protocol);
	if (bsd_fd < 0) {
		errno = bsd_errno;
		return -1;
	}
	int fd = socket_from_bsd(bsd_fd);
	if (fd < 0) {
		bsd_close(bsd_fd);
		return -1;
	}
	return fd;
}

int connect(int socket, const struct sockaddr *address, socklen_t address_len) {
	struct file *f = fd_file_get(socket);
	int bsd_fd = *((int*)f->data);
	if (f->ops != &socket_fops) {
		fd_file_put(f);
		// TODO: Set errno
		errno = ENOSYS;
		return -1;
	}
	fd_file_put(f);
	if (bsd_connect(bsd_fd, address, address_len) < 0) {
		errno = bsd_errno;
		return -1;
	}
	return 0;
}

ssize_t __socket_read(void *data, char *buf, size_t len) {
	int bsd_sock = *((int*)data);
	ssize_t ret;

	ret = bsd_recv(bsd_sock, buf, len, 0);
	if (ret < 0)
		ret = -bsd_errno;
	return ret;
}

ssize_t __socket_write(void *data, const char *buf, size_t len) {
	int bsd_sock = *((int*)data);
	ssize_t ret;

	ret = bsd_send(bsd_sock, buf, len, 0);
	if (ret < 0)
		ret = -bsd_errno;
	return ret;
}

int __socket_release(struct file *f) {
	int bsd_sock = *((int*)f->data);
	int ret = 0;
	if (bsd_close(bsd_sock) < 0)
		ret = -bsd_errno;
	// Release the data anyway. We assume close always works.
	free(f->data);
	return ret;
}

static struct file_operations socket_fops = {
	.read = __socket_read,
	.write = __socket_write,
	.release = __socket_release,
};
