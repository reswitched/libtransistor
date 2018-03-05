#include<vector>
#include<cstdio>

int main(int argc, char *argv[]) {
	std::vector<int> v;
	for(int i = 0; i < 256; i++) {
		printf("pushing %d\n", i);
		v.push_back(i);
	}
}
