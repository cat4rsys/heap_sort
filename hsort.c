#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdint.h>
char** array = NULL;
size_t swapCounter = 0;

void swap(char** a, char** b) {
	swapCounter++;
	char* c = *a;
	*a = *b;
	*b = c;
}

#define PARENT(e) (((e)-1)/2)
#define LEFT(e) (((e)+1)*2-1)
#define RIGHT(e) (((e)+1)*2)

int heapify(char** arr, int i, int s, int sz) {
    if (sz <= s ) return 0;

    if ( i == 0 || strcmp(arr[i], arr[PARENT(i)]) >0 ) return heapify(arr, s+1, s+1, sz);

    swap(&arr[i], &arr[PARENT(i)]);
    return heapify(arr, PARENT(i), s, sz);
}


int heapdown(char** arr, int i, int sz) {
	char *x = arr[i];
	char* min = x;
	int mini = i;
	if ( LEFT(i) < sz && strcmp(arr[LEFT(i)], x) < 0 )
		min = arr[LEFT(i)], mini = LEFT(i);
	if ( RIGHT(i) < sz && strcmp(arr[RIGHT(i)], min) < 0  ) 
		min = arr[RIGHT(i)], mini = RIGHT(i);
	if ( i != mini) {
		swap(&arr[i], &arr[mini]);
		return heapdown(arr, mini, sz);
	}
	return 0;

}

int sortify(char** arr, int sz) {
	if ( sz <= 1) return 0;
	swap(&arr[0], &arr[sz-1]);
	heapdown(arr, 0, sz-1);
	return sortify(arr, sz-1);
}

int heapsort(char** arr, int sz) {
	return heapify(arr, 1, 1, sz) || sortify(arr, sz);
}

#define SEC_TO_US(sec) ((sec)*1000000)
#define NS_TO_US(ns)   ((ns)/1000)

uint64_t micros()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    uint64_t us = SEC_TO_US((uint64_t)ts.tv_sec) + NS_TO_US((uint64_t)ts.tv_nsec);
    return us;
}

int main() {
	size_t cap = 1024;
	array = calloc(cap, sizeof(char*));
	char buf[4096];
	int i = 0;
	while (fgets(buf, sizeof(buf), stdin)) {
		if ( i >= cap) array = realloc(array, sizeof(char*)*(cap*=2));
		array[i++] = strdup(buf);
	}
	uint64_t timeStart = micros();
	heapsort(array, i);
	printf("%d %zu %zu", i, swapCounter, micros() - timeStart);
	free(array);
}
