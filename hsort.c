#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char** array = NULL;
static int swapCounter = 0;

void swap(char** a, char** b) {
	char* c = *a;
	*a = *b;
	*b = c;
	swapCounter++;
}

#define PARENT(e) (((e)-1)/2)
#define LEFT(e) (((e)+1)*2-1)
#define RIGHT(e) (((e)+1)*2)

int heapify(char** arr, int i, int sz) {
	if ( sz <= 1) return 0;
	if ( i == 0 ) return heapify(arr, sz-2, sz-1);
	if ( strcmp(arr[i], arr[PARENT(i)]) > 0 )
		swap(&arr[i], &arr[PARENT(i)]);
	return heapify(arr, PARENT(i), sz);
}

int heapdown(char** arr, int i, int sz) {
	char *x = arr[i];
	char* min = x;
	int mini = i;
	if ( LEFT(i) < sz && strcmp(arr[LEFT(i)], x) > 0 )
		min = arr[LEFT(i)], mini = LEFT(i);
	if ( RIGHT(i) < sz && strcmp(arr[RIGHT(i)], min) > 0  )
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
	return heapify(arr, sz-1, sz) || sortify(arr, sz);
}


int main() {
	size_t cap = 1024;
	array = calloc(cap, sizeof(char*));
	char buf[4096];
	int i;
	while (fgets(buf, sizeof(buf), stdin)) {
		if ( i >= cap) array = realloc(array, sizeof(char*)*(cap*=2));
		array[i++] = strdup(buf);
	}
	/*fprintf(stderr, "Sorting....\n");*/
	heapsort(array, i);
	/*fprintf(stderr, "Heapified\n");
	for ( int j = 0; j < i; j++ )
		fputs(array[j], stdout);
	free(array);*/

	printf("Total amount of swaps: %d\nTotal amount of lines: %d\n", swapCounter, i);
}
