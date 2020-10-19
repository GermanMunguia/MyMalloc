#include <stdio.h>
#include <stdlib.h>

int main () {

	for(int i = 0; i < 5; i++) {
		int *t = malloc(2); 

		printf("%p\n", &t);
	
	}


}
