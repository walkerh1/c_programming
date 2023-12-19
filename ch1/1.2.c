#include <stdio.h>

// print some \c that is not a valid escape sequence

int main(){
	printf("\"\\d\" just prints \"\d\"\n");
	return 0;
}