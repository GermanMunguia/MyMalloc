#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mymalloc.h"
#define DEBUG 1
#define CLEAN 1 

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
		printf("Invalid call to free\nfile:%s\nline:%d\n", file, line);
		return; 
	}
	
	//run through the meta data, check if given pointer exist or is being used. 
	void* ptrBlock = myblock; 
	int memSize = 0; 
	//create a way to access the previous metadata.
	meta *prev = NULL; 
	for(meta *crnt = ptrBlock; crnt != NULL; crnt = crnt->next ) {
			void *ptrCrnt = &crnt->inUse; 	
			printf("	COMPARING 	%p to %p\n\n", ptrCrnt+sizeof(meta), ptr );	
			//the ptr that was called on is found, check if it can be freed or not
			if((ptrCrnt+sizeof(meta)) == ptr) {

				//Free it since it is inUse
				if(crnt->inUse == 1) {
					if(DEBUG) {
						printf("\n\nThe pointer of size %d was found and freed\n\n", crnt->size);
					}
					//sets the values of the return pointers to 0. 
					if(CLEAN) {

						for(int i = (memSize+sizeof(meta)); i < (memSize+crnt->size+sizeof(meta)); i++) {
							myblock[i] = 0; 
						}
					}

					crnt->inUse = 0; 

					//Now check for other possible neighboring Free block to merge with.
					
					//the free is between two other freed metadata.  
					if(prev != NULL && crnt->next != NULL) {
						if(prev->inUse == 0 && crnt->next->inUse == 0) {
							if(DEBUG) {
								printf("The block is inbetween two freed blocks, merging all three\n");
							}

							int oldSize = crnt->size; 
							int oldSize2 = prev->size; 
							int oldSize3 = crnt->next->size; 

							prev->size = (prev->size+sizeof(meta)+sizeof(meta)+crnt->size+crnt->next->size);
							prev->next = crnt->next->next;
						       	crnt = prev; 	


							if(CLEAN) {
								printf("memSize: %d, crntSize: %d, oldSize: %d  %d   %d \n", memSize, crnt->size, oldSize, oldSize2, oldSize3);
								for(int i = (memSize - oldSize2); i < (memSize - oldSize2 + sizeof(meta)+oldSize2+sizeof(meta)+oldSize+oldSize3); i++) {
									myblock[i] = 0; 
								}
							}

							return;

						}
					}

					if(prev != NULL) {

						//the previous block is also free, merge them 
						if(prev->inUse == 0) {
							if(DEBUG) {
								printf("The previous block was also free, both are merged\n");
							}
						
							int oldSize = crnt->size; 

							//merge the previous block
							prev->size = (prev->size+sizeof(meta)+crnt->size); 
							prev->next = prev->next->next; 
							crnt = prev; 


							if(CLEAN) {

								for(int i = (memSize); i < (memSize+sizeof(meta)+oldSize); i++) {
									myblock[i] = 0; 
								}
							}

							return; 
							
						}
						

					}

					if(crnt->next != NULL) {
						//the next block is also not in use, therefore merge it
						if(crnt->next->inUse == 0) {
							if(DEBUG) {
								printf("The next block is also free, both are merged\n");
							}
							
							int oldSize = crnt->next->size; 

							crnt->size = (crnt->size+sizeof(meta)+crnt->next->size); 
							crnt->next = crnt->next->next; 

							printf("memSize: %d, crntSize: %d, oldSize: %d\n", memSize, crnt->size, oldSize);
							if(DEBUG) {
								for(int i = (memSize+sizeof(meta)); i < (memSize+sizeof(meta)+sizeof(meta)+(crnt->size-oldSize)); i++) {
									myblock[i] = 0;
								}	
							}

							return; 
							
						}
					}

						
					return;
				}	
				//(2)The pointer is not being used. 
				else{
					printf("Invalid call to free, pointer already has been freed\nfile:%s\nline:%d\n", file, line);
					return; 
				}

			}
			//move the previous foward
			prev = crnt; 

		if(DEBUG) {
			printf("crnt ptr located at: %p\n", &crnt);
			printf("	inUse: %p\n", (&crnt->inUse));
			printf("	size: %p	size=%d\n", &crnt->size, crnt->size);
			printf("	next: %p\n", &crnt->next);
			printf("	should be:%p\n", (myblock+memSize) );
			printf("	memSize: %d\n", memSize);	
			memSize = memSize + sizeof(meta) + crnt->size;
		}
	}


	//(3) the pointer was not found.
	if(DEBUG) {
	 printf("\n\nThe pointer was never found\n\n");  
	}	
	printf("Invalid call to free\nfile:%s\nline:%d\n", file, line);
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
		//If the block is much larger, break it and create another meta data block to account for the rest of the freed space. 
		////if the remaining block is not large enough to hold a meta data block, then return the extra space since it is useless anyways. 
		if(crnt->inUse == 0) {
			
			//it is just the right size
			if(size == crnt->size) {
		
				if(DEBUG) {
					printf("A freed block was available of the same size\n");
				}

				//make it inUse and return the pointer. 
				crnt->inUse = 1;
			       	void* r = crnt; 	
				return (r+sizeof(meta)); 		
			}

			//the size that is asked for is less than is available, split into another block
			if(size < crnt->size) {

				//there is not enough room to hold another meta data block, return the pointer with extra space
				if(size + sizeof(meta) > crnt->size) {
					crnt->inUse = 1;
			       		void* r = crnt; 	
					return (r+sizeof(meta)); 
				}
				
				//split into two block of meta data
				
				if(DEBUG) {
					printf("SPLITTING A BLOCK INTO TWO, starting:%ld \n", (memUsed - crnt->size - sizeof(meta)));
				}
		
				if(DEBUG) {
					printf("Attempted to create a new metadata at %ld   of size %ld\n", memUsed-crnt->size+size, (crnt->size-sizeof(meta)-size));
				}
				
				//create the new block at the appropriate location	
				meta *temp = (meta*) (myblock+memUsed-crnt->size+size);
				//since it will be empty set it to free
				temp->inUse = 0; 
				temp->size = (crnt->size-sizeof(meta)-size); 
				temp->next = crnt->next;
				crnt->next = temp; 
			
				//return the pointer at the same spot since that did not change. 
				crnt->size = size;
				crnt->inUse = 1; 
				void* r = crnt;
				return (r+sizeof(meta));

			}
			

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
			//MUST USE parenthesis for addition, otherwise it will add by a size of the struct. 		
			meta *temp = (meta*) (myblock+memUsed);
		       	

		       	printf("being made in address: %p with a memUsed of %d\n", myblock+memUsed, memUsed);	
			temp->size = size;
			temp->inUse = 1;
			temp->next = NULL;
		 	//copy the mem to the array
			printf("memcpy to address: %p\n", &temp);
//			memcpy(myblock+memUsed, temp, sizeof(meta));
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
	
	

	//this should not be reached.  
	return NULL;  	
}



