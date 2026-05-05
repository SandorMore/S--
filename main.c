#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv){
	for(size_t i = 1; i <= argc; ++i){
		printf("%s\n", argv[i]);
	}
	return 0;
}
