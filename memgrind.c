
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "mymalloc.h"

int main() {

///*
	struct timeval timer;
	gettimeofday(&timer, NULL); 
	time_t startTime = timer.tv_sec;
       	time_t startTime2 = timer.tv_usec; 	
	double times[50]; 

/*

	for(int workload = 0; workload < 1; workload++) {

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
			//
		printMem(); 
		malloc(4000);


		//time the workload	
		gettimeofday(&timer, NULL);
		time_t micro = (timer.tv_usec - startTime2); 
		time_t seconds = (timer.tv_sec - startTime); 
		double toSeconds = micro;
		toSeconds /= 1000000;
		times[workload] = (toSeconds+seconds);	
		//printMem();
	}



	for(int i = 0; i < 1; i++) {
		printf("Time: %f\n", times[i]);
	}
*/


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


	char* ptr4 = malloc(22*sizeof(char));
	for(int i = 0; i < 22; i++) {
		ptr4[i] = 'y'; 
		
	}

//	free(ptr2); 

	printMem();

/*
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

	printMem();

	char* ptr8 = malloc(120*sizeof(char));

//	printMem();

//	free(ptr3);
//	free(ptr3);
//	int p1 = 2;	
//	int *p = &p1; 
//	free(p);
*/

}
