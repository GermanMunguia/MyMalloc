
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "mymalloc.h"

//implementate test cases to run. 
int main() {

	struct timeval timer;
	gettimeofday(&timer, NULL); 
	time_t startTime = timer.tv_sec;
       	time_t startTime2 = timer.tv_usec; 	
	double times[50];

	for(int workload = 0; workload < 50; workload++) {

		//test case A
			//malloc one byte and free it 120 times

		char* ptr; 	
		for(int i = 0; i < 120; i++) {
			ptr = malloc(1*sizeof(char));
			free(ptr);
		}

		//test case B 
			//malloc 1 byte and store it in an array 120 times, then free them 1 by 1
		
		void* arr[120]; 
		for(int i = 0; i < 120; i++) {
			arr[i] = malloc(1);		
		}

		for(int i = 0; i < 120; i++) {
			free(arr[i]);
		}


		//test case C
			//Randomly malloc or free 1 byte pointers 240 times
		
		//keep track of number of avaliable pointer
		int pointerCount = 0; 
		int mallocCount = 0;
		int freeCount = 0; 	

		//keep track of the malloc pointers
		void* arr2[120];

		for(int i = 0; i < 240; i++) {
		
			//if pointerCount is 0, then cannot free, must malloc and store in the array 	
			if(pointerCount == 0) {

				//printf("pointerCount: %d\tMust allocate\tmallocCount: %d\tfreeCount: %d\n", pointerCount, mallocCount, freeCount);

				arr2[pointerCount] = malloc(1); 
				pointerCount++; 
				mallocCount++; 
				continue; 
			}

			//if there are already 120 mallocs then it must free
			if(mallocCount == 120) {

				//printf("pointerCount: %d\t Max mallocs reach: %d\tfreeCount: %d\n", pointerCount, mallocCount, freeCount);

				free(arr2[pointerCount-1]);
				pointerCount--; 
				freeCount++; 
				continue; 
			}
			
			//randomly generate a number between 0 and 1
			int random = (rand() % 2);

			//if 0 then malloc
			if(random == 0) {
				
				//printf("pointerCount: %d\tRandomly chose to malloc\tmallocCount: %d\tfreeCount: %d\n", pointerCount, mallocCount, freeCount);

				arr2[pointerCount] = malloc(1); 
				pointerCount++;
				mallocCount++;
				continue; 
			}

			//if 1 then free
			if(random == 1) {

				//printf("pointerCount: %d\tRandomly chose to free  \tmallocCount: %d\tfreeCount: %d\n", pointerCount, mallocCount, freeCount);

				free(arr2[pointerCount-1]);
				pointerCount--;
				freeCount++; 
				continue;	
			}

		}


		//test case D
			//malloc 315 total 1 byte pointers and store them all at once, then free them. 
		void* arr3[315]; 
		for(int i = 0; i < 315; i++) {
			arr3[i] = malloc(1); 
		}
	
		for(int i = 0; i < 315; i++) {
			free(arr3[i]);
		}

		//test case E
			//malloc 256 total int sized byte pointers, then free each odd numbered index, then free each even index pointer in backwards order

		void* arr4[256]; 
		for(int i = 0; i < 256; i++) {
			arr4[i] = malloc(1*sizeof(int));
		}
		//now free the odd 
		for(int i = 0; i < 256; i++) {
			if(i % 2 == 1) {
				free(arr4[i]);
			}
		}

		//now the even in backwards order
		for(int i = 255; i >= 0; i--) {
			if(i % 2 == 0) {
				free(arr4[i]);
			}
		}

		//time the workload	
		gettimeofday(&timer, NULL);
		time_t micro = (timer.tv_usec - startTime2); 
		time_t seconds = (timer.tv_sec - startTime); 
		double toSeconds = micro;
		toSeconds /= 1000000;
		times[workload] = (toSeconds+seconds);	
	}


	double AverageTime = 0; 
	for(int i = 0; i < 50; i++) {
		AverageTime += times[i]; 
		printf("Workload # %d : %f seconds\n", i+1, times[i]);
	}
	printf("Total time: %f\nAverage Time: %f\n", AverageTime, (AverageTime/50));

}
