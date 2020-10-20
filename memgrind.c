#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

int main() {

	void* ptrNULL;
	free(ptrNULL);

	char* ptr = malloc(10*sizeof(char));
	for(int i = 0; i < 10; i++) {
		ptr[i] = 'a'; 
	}
	char* ptr2 = malloc(20*sizeof(char));
	for(int i = 0; i < 20; i++) {
		ptr2[i] = 'b'; 
		
	}
	int* ptr3 = malloc(8*sizeof(int));
	for(int i = 0; i < 8; i++) {
		ptr3[i] = 50; 
		
	}

	char* ptr4 = malloc(4*sizeof(char));
	for(int i = 0; i < 4; i++) {
		ptr4[i] = 'y'; 
		
	}

	free(ptr3);
			

	printf("pointer to ptr %p\n", ptr);
       	printf("pointer to ptr2 %p\n", ptr2);


}
