#include<libtransistor/nx.h>

#include<stdio.h>

int main() {
	for(int i = 0; i < 8000; i++) {
		result_t r = hid_init();
		printf("%d -> 0x%x\n", i, r);
		if(r != RESULT_OK) {
			return 1;
		}
		hid_finalize();
	}
	return 0;
}
