/*
 * Author: Mary Gwyneth A. Tolentino
 * Section: B-5L
 * Program Description: Attaches to the shared memory, computes the right half of the matrix product,
 *  and displays the final result in the terminal once all computations are complete.
 */
 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>	//for new types declared
#include<sys/ipc.h>		//for interprocess communication
#include<sys/shm.h>		//for shared memory
#define MAT_SIZE_KEY 16
#define MAT_A_KEY 17
#define MAT_B_KEY 18
#define MAT_RESULT_KEY 19

int main(){
    // for matrix sizes
	key_t mat_size_key = MAT_SIZE_KEY;
	int mat_size_segment_id;
	int *mat_size_shared_memory;

    // for matrix A
	key_t matA_key = MAT_A_KEY;
	int matA_segment_id;
	int *matA_shared_memory;

    // for matrix B
	key_t matB_key = MAT_B_KEY;
	int matB_segment_id;
	int *matB_shared_memory;

	// for the computed/resulting matrix
	key_t mat_result_key = MAT_RESULT_KEY;
	int mat_result_segment_id;
	int *mat_result_shared_memory;

	int i;

    // MATRIX SIZES - shmget and shmattach
	mat_size_segment_id = shmget(mat_size_key, 5*sizeof(int), 0666);

	if(mat_size_segment_id < 0)
    {
		printf("shmget error\n");
		exit(1);
	}

	mat_size_shared_memory = shmat(mat_size_segment_id, NULL, 0);

	if(mat_size_shared_memory == (int *) -1)
    {
		printf("shmat error\n");
		exit(1);
	}

    // Column of Matrix A must be equal to the row of Matrix B
	if (mat_size_shared_memory[1] != mat_size_shared_memory[2]) 
    {   
		printf("Cannot perform matrix multiplication!\n");
		exit(1);
	} 


	// MATRIX A - shmget and shmattach
	matA_segment_id = shmget(matA_key, mat_size_shared_memory[0]*mat_size_shared_memory[1]*sizeof(int), 0666);

	if(matA_segment_id < 0)
    {
		printf("shmget error\n");
		exit(1);
	}

	matA_shared_memory = shmat(matA_segment_id, NULL, 0);

	if(matA_shared_memory == (int *) -1)
    {
		printf("shmat error\n");
		exit(1);
	}

	// MATRIX B - shmget and shmattach
	matB_segment_id = shmget(matB_key, mat_size_shared_memory[2]*mat_size_shared_memory[3]*sizeof(int), 0666);

	if(matB_segment_id < 0)
    {
		printf("shmget error\n");
		exit(1);
	}

	matB_shared_memory = shmat(matB_segment_id, NULL, 0);

	if(matB_shared_memory == (int *) -1)
    {
		printf("shmat error\n");
		exit(1);
	}

    // Store the dimensions of matrices A and B
	int a_row = mat_size_shared_memory[0];
	int a_col = mat_size_shared_memory[1];
	int b_row = mat_size_shared_memory[2];
	int b_col = mat_size_shared_memory[3];
	
	// RESULTING MATRIX - shmget and shmattach
	int mat_result_size = a_row*b_col;
	mat_result_segment_id = shmget(mat_result_key, mat_result_size*sizeof(int), 0666);

	if(mat_result_segment_id < 0)
    {
		printf("shmget error\n");
		exit(1);
	}

	mat_result_shared_memory = shmat(mat_result_segment_id, NULL, 0);

	if(mat_result_shared_memory == (int *) -1)
    {
		printf("shmat error\n");
		exit(1);
	}

	if(mat_result_segment_id < 0)
    {
		printf("shmget error\n");
		exit(1);
	}

	mat_result_shared_memory = shmat(mat_result_segment_id, NULL, 0);

	if(mat_result_shared_memory == (int *) -1)
    {
		printf("shmat error\n");
		exit(1);
	}

	// Compute the other half of the matrix
	int mat_result_index = mat_size_shared_memory[5]; //current index of the resulting matrix that is empty
	int first_half = a_row/2;               //first half of the computation
	int a_index = (first_half+1)*(a_row);   //current index in the 1-D array

	for (int k = 0; k < first_half+1; k++) 
    {   //loop over the rows of the second half of matrix A
		int b_index = 0;

		for (int l = 0; l < b_col; l++) 
        {   // loop over columns in matrix B
			int sum = 0;
			int a_temp = a_index;
			int b_temp = b_index;

			for (int m = 0; m < a_row; m++) 
            {   // perform dot product
				sum += matA_shared_memory[a_temp] * matB_shared_memory[b_temp];
				a_temp++;           //move to the next element in matrix A's row
				b_temp += b_col;    //move down in matrix B's column
			}
			mat_result_shared_memory[mat_result_index] = sum;
			mat_result_index++;

			b_index++;
		}
        // move to the next row in matrix A
		a_index += a_row;
	}

    // PRINT RESULTING MATRIX
	int index = 0;
	for (int k = 0; k < a_row; k++) 
    {
		for (int l = 0; l < b_col; l++) 
        {
			printf("%d\t", mat_result_shared_memory[index++]);
		}
		printf("\n");
	}

	shmdt(mat_size_shared_memory);
	shmdt(matA_shared_memory);
	shmdt(matB_shared_memory);
	shmdt(matB_shared_memory);
	shmdt(mat_result_shared_memory);
}