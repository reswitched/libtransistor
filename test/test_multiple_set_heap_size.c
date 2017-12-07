// regression test for Mephisto #13 (https://github.com/reswitched/Mephisto/pull/13)

#include<libtransistor/types.h>
#include<libtransistor/svc.h>

int main(int argc, char *argv[]) {
	void *heap;
	svcSetHeapSize(&heap, 0x1000);
	svcSetHeapSize(&heap, 0x2000);
	svcSetHeapSize(&heap, 0x8000);
	svcSetHeapSize(&heap, 0x1000);
	return 0;
}
