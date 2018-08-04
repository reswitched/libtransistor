#include<libtransistor/nx.h>
#include<libtransistor/fd.h>

#include<sys/socket.h>
#include<stdlib.h>
#include<errno.h>

static trn_file_ops_t socket_fops;

int socket_from_bsd(int bsd_fd) {
	int *bsd_fd_mem = malloc(sizeof(*bsd_fd_mem));
	
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
	trn_file_t *f = fd_file_get(socket);
	if (f == NULL) {
		errno = EBADF;
		return -1;
	}
	int bsd_fd = *((int*)f->data);
	if (f->ops != &socket_fops) {
		fd_file_put(f);
		errno = ENOTSOCK;
		return -1;
	}
	fd_file_put(f);
	if (bsd_connect(bsd_fd, address, address_len) < 0) {
		errno = bsd_errno;
		return -1;
	}
	return 0;
}

int accept(int socket, struct sockaddr *address, socklen_t *address_len) {
	trn_file_t *f = fd_file_get(socket);
	if (f == NULL) {
		errno = EBADF;
		return -1;
	}
	int bsd_fd = *((int*)f->data);
	int bsd_client_fd = -1;
	if (f->ops != &socket_fops) {
		fd_file_put(f);
		errno = ENOTSOCK;
		return -1;
	}
	fd_file_put(f);
	if ((bsd_client_fd = bsd_accept(bsd_fd, address, address_len)) < 0) {
		errno = bsd_errno;
		return -1;
	}

	int fd = socket_from_bsd(bsd_client_fd);
	if (fd < 0) {
		bsd_close(bsd_client_fd);
		return -1;
	}
	return fd;
}

int bind(int socket, const struct sockaddr *address, socklen_t address_len) {
	trn_file_t *f = fd_file_get(socket);
	if (f == NULL) {
		errno = EBADF;
		return -1;
	}
	int bsd_fd = *((int*)f->data);
	if (f->ops != &socket_fops) {
		fd_file_put(f);
		errno = ENOTSOCK;
		return -1;
	}
	fd_file_put(f);
	if (bsd_bind(bsd_fd, address, address_len) < 0) {
		errno = bsd_errno;
		return -1;
	}
	return 0;
}

int listen(int socket, int backlog) {
	trn_file_t *f = fd_file_get(socket);
	if (f == NULL) {
		errno = EBADF;
		return -1;
	}
	int bsd_fd = *((int*)f->data);
	if (f->ops != &socket_fops) {
		fd_file_put(f);
		errno = ENOTSOCK;
		return -1;
	}
	fd_file_put(f);

	if (bsd_listen(bsd_fd, backlog) < 0) {
		errno = bsd_errno;
		return -1;
	}
	return 0;
}

ssize_t recv(int socket, void *message, size_t length, int flags) {
	trn_file_t *f = fd_file_get(socket);
	if (f == NULL) {
		errno = EBADF;
		return -1;
	}
	int bsd_fd = *((int*)f->data);
	ssize_t ret;

	if (f->ops != &socket_fops) {
		fd_file_put(f);
		errno = ENOTSOCK;
		return -1;
	}
	fd_file_put(f);

	ret = bsd_recv(bsd_fd, message, length, flags);
	if (ret < 0) {
		ret = -1;
		errno = bsd_errno;
	}
	return ret;
}

ssize_t send(int socket, const void *data, size_t length, int flags) {
	trn_file_t *f = fd_file_get(socket);
	if (f == NULL) {
		errno = EBADF;
		return -1;
	}
	int bsd_fd = *((int*)f->data);
	ssize_t ret;

	if (f->ops != &socket_fops) {
		fd_file_put(f);
		errno = ENOTSOCK;
		return -1;
	}
	fd_file_put(f);

	ret = bsd_send(bsd_fd, data, length, flags);
	if (ret < 0) {
		ret = -1;
		errno = bsd_errno;
	}
	return ret;
}

static result_t __socket_read(void *data, void *buf, size_t len, size_t *bytes_read) {
	int bsd_sock = *((int*)data);
	ssize_t ret;

	ret = bsd_recv(bsd_sock, buf, len, 0);
	if (ret < 0) {
		return bsd_result;
	}

	*bytes_read = ret;
	return RESULT_OK;
}

static result_t __socket_write(void *data, const void *buf, size_t len, size_t *bytes_written) {
	int bsd_sock = *((int*)data);
	ssize_t ret;

	ret = bsd_send(bsd_sock, buf, len, 0);
	if (ret < 0) {
		return bsd_result;
	}

	*bytes_written = ret;
	return RESULT_OK;
}

static result_t __socket_release(trn_file_t *f) {
	int bsd_sock = *((int*)f->data);
	result_t ret = RESULT_OK;
	if (bsd_close(bsd_sock) < 0)
		ret = bsd_result;
	// Release the data anyway. We assume close always works.
	free(f->data);
	return ret;
}

static trn_file_ops_t socket_fops = {
	.read = __socket_read,
	.write = __socket_write,
	.release = __socket_release,
};
