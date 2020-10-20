#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

int main() {

	char* ptr = malloc(15*sizeof(char));
	for(int i = 0; i < 15; i++) {
		ptr[i] = 'a'; 
	}
	int* ptr2 = malloc(10*sizeof(int));
	for(int i = 0; i < 10; i++) {
		ptr2[i] = 2; 
		
	}
	char* ptr3 = malloc(20*sizeof(char));
	for(int i = 0; i < 20; i++) {
		ptr3[i] = 'x'; 
		
	}

	char* ptr4 = malloc(2*sizeof(char));
	for(int i = 0; i < 2; i++) {
		ptr4[i] = 'y'; 
		
	}


			

	printf("pointer to ptr %p\n", ptr);
       	printf("pointer to ptr2 %p\n", ptr2);


}
