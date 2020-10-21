#define malloc(x) mymalloc(x,__FILE__, __LINE__)
#define free(x) myfree(x,__FILE__, __LINE__)

#include <stdlib.h>
#pragma pack(1)
typedef struct meta {
	short int inUse;
	short int size;
	struct meta *next;  

} meta; 

void *mymalloc(size_t size, char *file, int line);
void myfree(void* ptr, char* file, int line);
void printMem(); 
