/* 2021-02990
 * Author: Mary Gwyneth A. Tolentino
 * Section: B-5L
 */

#include<stdio.h>
#include<stdlib.h> //for malloc
#include<pthread.h> //for threads

typedef struct ARG{
	int Arow;
	int Bcol;
	int ans;
}args;

int **A;
int **B;
int numRowA, numRowB;
int numColA, numColB;


// Initialize 2D array dynamically
int * init_data(FILE *fp, int ***data_ptr, int dim_x, int dim_y)
{
	int **data = (int **) malloc(sizeof(int *) * dim_x);
	for (int i = 0; i < dim_x; i++) 
	{
		data[i] = (int *) malloc(sizeof(int) * dim_y);
	}

	for (int j = 0; j < dim_x; j++) {
		for (int k = 0; k < dim_y; k++) {
			fscanf(fp, "%d ", &data[j][k]);
		}
	}

  *data_ptr = data;
}


void * caculateMatrix(void *argument){
	args * temp = (args *) argument;

	// printf("Number: %d %d\n", temp->Arow, temp->Bcol);
	temp->ans = 0;
	for (int i = 0; i < numRowA; i++) {
		// increment columns in A while rows in B (multiply row of A and column of B`)
		temp->ans += A[temp->Arow][i] * B[i][temp->Bcol];
	}
	
	pthread_exit(NULL);
}


int main(){
	// args *arguments; //dynamic number of arguments since the number of threads is unknown;
	//pwede nyo tong gawing 2D array, mahihirapan lang kayo mag-loop
	int counter;
	FILE *fp = fopen("matrix.in", "r");
	if (fp != NULL) {
		//read file here
		//you can use fscanf for reading the first and second lines
		fscanf(fp, "%d\n", &counter);

		for (int i = 0; i < counter; i++) {
			// 	MATRIX A - initialization
			fscanf(fp, "%d %d\n", &numRowA, &numColA);
			init_data(fp, &A, numRowA, numColA);

			// print matrix A
			printf("MATRIX A:\n");
			for (int j = 0; j < numRowA; j++) {
				for (int k = 0; k < numColA; k++) {
					printf("%d ", A[j][k]);
				}
				printf("\n");
			}

			printf("\n");

			// 	MATRIX B - initialization
			fscanf(fp, "%d %d\n", &numRowB, &numColB);
			init_data(fp, &B, numRowB, numColB);


			// check if the size is invalid, i.e. colA != rowB
			if (numColA != numRowB) {
				printf("Invalid Matrix Sizes!\n");
				exit(1); // terminate the program
			}

			// print matrix B
			printf("MATRIX B:\n");
			for (int j = 0; j < numRowB; j++) {
				for (int k = 0; k < numColB; k++) {
					printf("%d ", B[j][k]);
				}
				printf("\n");
			}

			printf("\n");
		
			//dynamic number of arguments since the number of threads is unknown;
			args *arguments = (args *)malloc(sizeof(args) * (numRowA * numColB));
			pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * (numRowA * numColB));


			//create your threads here. Pass to the thread the row of A and the column of B they need to check.
			int index = 0;
			for(int l = 0; l < numRowA; l++) {
				for (int m = 0; m < numColB; m++) {
					arguments[index].Arow = l;
					arguments[index].Bcol = m;
					pthread_create(&tid[index], NULL, caculateMatrix, (void *) &arguments[index]);
					index++;
				}
			}

			//join your threads here
			for (int k = 0; k < numRowA * numColB; k++) {
				pthread_join(tid[k], NULL);
			}

			//manage the return values of the threads here
			//print the solution heres
			index = 0;
			printf("RESULTING MATRIX DERIVED FROM A x B:\n");
			for (int i = 0; i < numRowA; i++) {
				for (int j = 0; j < numColB; j++) {
					printf("%d ", arguments[index].ans);
					index++;
				}
				printf("\n");
			}
			printf("\n");

			// Free allocated memory
			free(tid);
			for (int j = 0; j < numRowA; j++) free(A[j]);
			free(A);
			for (int j = 0; j < numRowB; j++) free(B[j]);
			free(B);
			free(arguments);
		}

		fclose (fp);

	}

	else printf("File not found!\n");
}	