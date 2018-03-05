#include<cstdio>

void func(int val) {
	throw val;
}

int main() {
	try {
		func(4445);
	} catch(int caught) {
		printf("caught %d\n", caught);
		if(caught == 4445) {
			return 0;
		}
	}
	return 2;
}
