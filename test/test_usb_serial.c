#include<libtransistor/util.h>
#include<libtransistor/svc.h>
#include<libtransistor/usb_serial.h>
#include<stdio.h>
#include<unistd.h>

static const char message[] = "hello from test_usb_serial.c\n";

int main(int argc, char *argv[]) {
	result_t r;
	ASSERT_OK(fail, usb_serial_init());
	size_t written;
	ASSERT_OK(fail, usb_serial_write(message, sizeof(message), &written));
	printf("wrote %ld/%ld bytes\n", written, sizeof(message));

	char buf[0x40];
	size_t read;
	ASSERT_OK(fail, usb_serial_read(buf, sizeof(buf), &read));
	printf("read %ld/%ld bytes\n", read, sizeof(buf));
	
	svcSleepThread(5000000000);

	dbg_printf("setting up USB stdio");
	int fd = usb_serial_open_fd();
	dbg_printf("got fd -> %d", fd);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	dup2(fd, STDIN_FILENO);
	printf("hello USB console?\n");
	printf("this is the second line.\n");

	int ch;
	while((ch = getc(stdin)) != '.' && (ch != -1)) {
		printf("got '%d'\n", ch);
	}
	
	usb_serial_finalize();
fail:
	return r != RESULT_OK;
}
