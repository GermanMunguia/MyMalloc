#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mymalloc.h"
//struct that will hold metadata
typedef struct meta { 
	int inUse; 
	int size; 
	struct meta *next; 
} meta;

static char myblock[4096];


int pop = 0; 


void ran() {

	myblock[0] = 'a'; 
	myblock[2] = 'b';
	myblock[16] = 'c';
}


//return a char pointer? 
void* mymalloc(size_t size, char* file, int line) {


	//the array is empty
	if(pop == 0) {
		//create a new struct to hold the first block allocated. 
		meta front;
		front.inUse = 1; 
		front.size = size;
	       	front.next = NULL; 	
		printf("size of meta: %lu\n", sizeof(front));
		//memcopy the struct onto the array
		memcpy(myblock, &front, sizeof(front));
		//create the unspecified pointer that will be returned for the user. 
		void* ptr = myblock+sizeof(front);
		pop = 1;
	       	return ptr;	
	}

	//array is not empty, search for a node of empty metadata to store the mem, or create a new. 
	//create a pointer at the front of the block to access the first set of metadata. 
	void *r = myblock;
       	int memUsed = 0; 	
	//traverse through all of the meta data that can either be in use or free. 
	for(meta *crnt = r; crnt != NULL; crnt = crnt->next ) {			

		//keep track of the total mem used that way the next meta location is known if one needs to be made.  
		memUsed= memUsed + crnt->size + sizeof(meta);
		printf("block size: %d inUse: %d      block+meta %ld\n", crnt->size, crnt->inUse, crnt->size+sizeof(meta));	
		
		//If unused then check if there is enough memory to store inside; 
		if(crnt->inUse == 0) {
			//TODOOOO

		}

		//The last meta data was reached, a new block must be allocated. 
		if(crnt->next == NULL) {

			//check if there is enough space left 
			printf("Total space used so far: %d\n", memUsed);
			
			if(memUsed + size + sizeof(meta) > 4096) {
				printf("NOT ENOUGH SPACE\n");
				return NULL;
			}

			//There is enough memory, create more metadata to account for it.
			
			// This code words but uses malloc

			printf("        New Meta appended after %d for size %ld at index: %d\n", crnt->size, size, memUsed);	
			meta *temp = (meta*) myblock+memUsed;  
			temp->size = size;
			temp->inUse = 1;
			temp->next = NULL;
		 	//copy the mem to the array
			printf("memcpy to address: %p\n", &temp);
//			memcpy(myblock+memUsed, &temp, sizeof(meta));
//			printf("after memcpy, crnt size = %d\n", crnt->size);
			//creates a pointer to the struct in order to add it to the end of the link. 
			crnt->next = temp;
//			printf("Now crnt size = %d and next size = %d\n", crnt->size, crnt->next->size);
			//return the unspecified pointer. 
			void *ptr = myblock+memUsed+sizeof(meta); 
			return ptr; 
			
		}
		

		
	}
	
	

	//if this is reached then it was not able to be allocated, due to a lack of memory 
	return NULL;  	
}

/*
int main() {

//	ran();
	
	char* ptr = malloc(15*sizeof(char)); 

	
	printf("sizeof struct: %lu\n", sizeof(meta));
	int *ptr = mymalloc(10*sizeof(int));
	ptr[0] = 'x';
	ptr[1] = 'x';
	ptr[8] = 'x'; 
     	ptr[9] = 'x'; 
	char *ptr2 = mymalloc(12*sizeof(char));
	ptr2[0] = 'a'; 
	ptr2[1] = 'a'; 
	ptr2[11] = 'a'; 
	char *ptr3 = mymalloc(15*sizeof(char));
	ptr3[0] = 'g'; 
	ptr3[14] = 'g'; 

	int *ptr4 = mymalloc(2*sizeof(int));
	ptr4[0] = 22;
	ptr4[1] = 22; 

	char *ptr5 = mymalloc(500*sizeof(char));
	ptr5[499] = '2'; 

	printf("Address of myblock: %p    end of block: %p\n", myblock, myblock+4096);
	printf("Address of block+size: %p\n", myblock+sizeof(meta));
	printf("Address of returned pointer: %p\n", ptr3);
	printf("the block: ");
	
	for(int i = 0; i < 200; i++) {
		printf(" %d", myblock[i]);
	}
	printf("\n");
	
		
} 

*/


