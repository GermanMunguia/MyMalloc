#define malloc(x) mymalloc(x,__FILE__, __LINE__)
#include <stdlib.h>


void *mymalloc(size_t size, char *file, int line); 
