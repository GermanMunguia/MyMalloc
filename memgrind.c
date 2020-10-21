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


//	free(ptr2);


 
	char* ptr4 = malloc(22*sizeof(char));
	for(int i = 0; i < 22; i++) {
		ptr4[i] = 'y'; 
		
	}

	puts("calling ptr5to2");
	char* ptr5to2 = malloc(2*sizeof(char));

	for(int i = 0; i < 2; i++) {
		ptr5to2[i] = 45; 
	}

	char* ptr6 = malloc(20*sizeof(char));	
	for(int i = 0; i < 20; i++) {
		ptr6[i] = 46; 
	}

	char* ptr7 = malloc(2*sizeof(char)); 
	for(int i = 0; i < 2; i++) {
		ptr7[i] = 47;
	}

	free(ptr2);

	char* ptr10 = malloc(130*sizeof(char)); 

	free(ptr4);
	 char* ptr9 = malloc(120*sizeof(char));	
//
	free(ptr3); 


	char* ptr8 = malloc(120*sizeof(char));

/*

	free(ptr3);
	free(ptr3);
	int p1 = 2;	
	int *p = &p1; 
	free(p);
*/

	printf("pointer to ptr %p\n", ptr);
       	printf("pointer to ptr2 %p\n", ptr2);


}
