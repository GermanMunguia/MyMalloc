#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mymalloc.h"
#define DEBUG 1

//struct that will hold metadata
typedef struct meta { 
	int inUse; 
	int size; 
	struct meta *next; 
} meta;

static char myblock[4096];

//free the ptr that was previously allocated with mymalloc, check for all possible errors. 
void myfree(void* ptr, char* file, int line) {
	//(1) if null, do nothing
	if(ptr == NULL) {
		return; 
	}
	
	//run through the meta data, check if given pointer exist or is being used. 
	void* ptrBlock = myblock; 
	int memSize = 0; 
	for(meta *crnt = ptrBlock; crnt != NULL; crnt = crnt->next ) {
		printf("crnt ptr located at: %p\n", &crnt);
		printf("	inUse: %p\n", (&crnt->inUse));
		printf("	size: %p	size=%d\n", &crnt->size, crnt->size);
		printf("	next: %p\n", &crnt->next);
		printf("	should be:%p\n", (myblock+memSize) );
		printf("	memSize: %d\n", memSize);	
		memSize = memSize + sizeof(meta) + crnt->size;
	}


}

//return a void pointer 
void* mymalloc(size_t size, char* file, int line) {

	//create a pointer to the begining of the block, if the has a size initiallized to zero, then it must be empty and it is the first call to malloc
	void *f = myblock;
	meta *isEmpty = f; 
	//the array is empty
	if(isEmpty->size == 0) {
		//create a new struct to hold the first block allocated. 
		meta* front = (meta*) myblock; 
		front->inUse = 1; 
		front->size = size; 
		front->next = NULL;
		void* ptr = myblock+sizeof(meta); 
		printf("first meta located at: %p\n", &front);
		/*
		meta front;
		front.inUse = 1; 
		front.size = size;
	       	front.next = NULL; 	
		printf("size of meta: %lu\n", sizeof(front));
		//memcopy the struct onto the array
		memcpy(myblock, &front, sizeof(front));
		//create the unspecified pointer that will be returned for the user. 
		void* ptr = myblock+sizeof(front);
		*/

		if(DEBUG) {
			printf("	BLOCK BEINGS: %p	Ends: %p\n", myblock, myblock+4096);
		}
		
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

			printf("        New Meta appended after %d for size %ld at index: %d\n", crnt->size, size, memUsed);	
			meta *temp = (meta*) myblock+memUsed;  
			temp->size = size;
			temp->inUse = 1;
			temp->next = NULL;
		 	//copy the mem to the array
			printf("memcpy to address: %p\n", &temp);
			memcpy(myblock+memUsed, &temp, sizeof(meta));
			printf("address after memcpy: %p\n", &temp);
//			printf("after memcpy, crnt size = %d\n", crnt->size);
			//creates a pointer to the struct in order to add it to the end of the link. 
			crnt->next = temp;
//			printf("Now crnt size = %d and next size = %d\n", crnt->size, crnt->next->size);
			//return the unspecified pointer.
			
			if(DEBUG) {
				for(int i = 0; i < 4096; i++) {
					printf(" %d", myblock[i]);
				}
				printf("\n");
	
			}
			
			void *ptr = myblock+memUsed+sizeof(meta); 
			return ptr; 
			
		}
		

		
	}
	
	

	//if this is reached then it was not able to be allocated, due to a lack of memory 
	return NULL;  	
}



