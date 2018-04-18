#include<stdint.h>
#include<malloc.h>

int main(int argc, char *argv[]) {
	uint32_t *ptr = malloc(4);
	*ptr = 8;
	return *ptr;
}
