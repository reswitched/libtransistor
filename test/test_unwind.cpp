#define UNW_LOCAL_ONLY
#include<libunwind.h>

#include<stdio.h>

void show_backtrace() {
	unw_cursor_t cursor;
	unw_context_t uc;
	unw_word_t ip, sp;

	printf("show_bt\n");
	unw_getcontext(&uc);
	unw_init_local(&cursor, &uc);
	int res;
	while((res = unw_step(&cursor)) > 0) {
		unw_get_reg(&cursor, UNW_REG_IP, &ip);
		unw_get_reg(&cursor, UNW_REG_SP, &sp);
		printf("ip = %lx, sp = %lx\n", (long) ip, (long) sp);
	}
	printf("terminated with %d\n", res);
}

void __attribute__((noinline)) a() {
	printf("a\n");
	show_backtrace();
}

void __attribute__((noinline)) b() {
	printf("b\n");
	a();
}

void __attribute__((noinline)) c() {
	printf("c\n");
	b();
}

int main(int argc, char *argv[]) {
	printf("hello\n");
	c();
}
