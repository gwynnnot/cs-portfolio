/*
 * Name: Mary Gwyneth A. Tolentino 
 * Lab Section: U-2L 
 * Program Description: A program that implements a binary min-heap with the smallest value at the root
*/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int left(int index){
  return(2 * index); 
}

int right(int index){
  return(2 * index + 1); 
}

int parent(int index){
  return(index / 2); 
}

void printHeapHelper(HEAP *H, int index, int tabs){
	if(index > H->size) return;
	else{
		printHeapHelper(H, right(index), tabs + 1);
		for(int i=0; i<tabs; i++) printf("\t");
		printf("%d\n", H->heap[index]);
		printHeapHelper(H, left(index), tabs + 1);
	}
}

void printHeap(HEAP *H){
	if(H!=NULL && H->size>0){
		printHeapHelper(H, 1, 0);
	}else{
		printf("Empty heap!\n");
	}
}


// IMPLEMENT FUNCTIONS HERE


HEAP* createHeap(int maxSize)
{	// function for creating and initializing a heap
	HEAP *H = (HEAP *) malloc(sizeof(HEAP));
	// initializes fields of the structure
	H->heap = (int *) malloc((maxSize) *sizeof(int));
	H->size = 0;
	H->maxSize = maxSize;

	return H;	// returns the created heap

}

int isFull(HEAP *H)
{	// function for checking if heap exists and its size is equal to maxSize
	if (H != NULL && H->size == H->maxSize)
		return 1;	// heap is full
	return 0;	// heap is not yet full
}

int isEmpty(HEAP *H)
{	// function for checking if heap exists and its size is equal to 0
	if (H != NULL && H->size == 0)
		return 1; // heap is empty
	return 0;	
}


void clear(HEAP *H)
{	// function for clearing the heap 
	// while not literally deleting all items
	if (H != NULL && isEmpty(H) == 0)
		H->size = 0;	// set the heap size to 0
}


void swap(int *A, int *B)
{	// function for swapping integers in percolate functions
	int C;

	C = *A;
	*A = *B;
	*B = C;
}

void percolateUP(HEAP *H, int index)
{	// function for perculating up recursively until it reaches the root
	if (index > 0)
	{	// check if value of key is greater than the value of its parent
		if (H->heap[index] < H->heap[parent(index)])
		{	// swap and percolate up
			swap(&(H->heap[index]), &(H->heap[parent(index)]));
			percolateUP(H, parent(index));
		}	
	}
}

void insert(HEAP *H, int key)
{	// function for inserting a key to the heap
	if (isFull(H) == 0)
	{
		H->size++;	// number of elements in the array + 1
		// placing key in the next available location	
		H->heap[H->size] = key;

		percolateUP(H, H->size);// PERCOLATE UP 	
	}
	
	else printf("Heap is full!");
}


void percolateDown(HEAP *H, int index)
{	// function for perculating up recursively until no perculation is needed
	// IF IT HAS TWO CHILDREN, FIND THE SMALLER CHILD
	if (right(index) < H->size)
	{	// check if it has a right child (then it automatically has a left child)
		if ((H->heap[index] > H->heap[right(index)]) && (H->heap[left(index)] > H->heap[right(index)]))
		{	// check if node is greater than it its right child
			// and right child is smaller than the left child
			swap(&(H->heap[index]), &(H->heap[right(index)]));
			// PERCOLATE DOWN TO RIGHT CHILD
			percolateDown(H, right(index));	
		}

		else if (H->heap[index] > H->heap[left(index)])
		{	// node is greater than its left child
			swap(&(H->heap[index]), &(H->heap[left(index)]));
			// PERCOLATE DOWN TO LEFT CHILD
			percolateDown(H, left(index));	
		}
	}

	// IF IT ONLY HAS ONE CHILD
	else if (left(index) < H->size)
	{	// check if it has a left child
		if (H->heap[index] > H->heap[left(index)])
		// and if node is greater than its left  child
			swap(&(H->heap[index]), &(H->heap[left(index)]));
	}	// NO PERCULATION IS NEEDED SINCE IT IS NOW A LEAF
}

int deleteM(HEAP *H)
{	// function for deleting the minimum value or root
	if (H != NULL && isEmpty(H) == 0)
	{
		int del = H->heap[1];	// hold the root
		// swap root value with the last value in the heap
		swap(&(H->heap[1]), &(H->heap[H->size]));
		H->size--;				// decrease size of the heap
		
		percolateDown(H, 1);	// PERCOLATE DOWN 
		return del;				// remove the minimum value from the heap
	}

	else printf("Heap is empty!\n");
	return -1;
}




int main(){

	char command;
	int key, result, type;
    int* sorted;

	HEAP *H = createHeap(30);

	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d...\n", key);
				insert(H, key);
				break;
			case '-':
				printf("Removing root from tree...\n");
				result = deleteM(H); // result is unused
				break;
			case 'p':
				printf("Printing the heap (rotated +90 degrees)...\n");
				printHeap(H);
				printf("\n");
				break;
			case 'E':
				printf("Heap %s empty.\n", isEmpty(H)?"is":"is not");
				break;
			case 'F':
				printf("Heap %s full.\n", isFull(H)?"is":"is not");
				break;
			case 'C':
				printf("Removing all contents...\n");
				clear(H);
				break;
			/* uncomment this for postlab
			case '~':
				printf("The sorted version of the heap:\n");
				sorted = heapSort(H);
				for(key=1; key <= H->size; key++)
					printf("%4d", sorted[key]);
				printf("\n");
				free(sorted);
				break;
			*/
			case 'Q':
				free(H->heap);
				free(H);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}