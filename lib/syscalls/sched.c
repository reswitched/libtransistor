#include<libtransistor/nx.h>

int sched_yield() {
	return svcSleepThread(0) != 0 ? -1 : 0;
}
