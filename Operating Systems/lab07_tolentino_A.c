/*
 * Author: Mary Gwyneth A. Tolentino
 * Section: B-5L
 * Program Description: Reads two matrices from input.txt, creates shared memory, 
 * and computes the left half (and middle column if needed) of their matrix product.
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

	// for resulting matrix
	key_t mat_result_key = MAT_RESULT_KEY;
	int mat_result_segment_id;
	int *mat_result_shared_memory;

	int i;

	// Allocate shared memory for matrix size info
    // matrix sizes are stored as: matA rows, matA columns, matB rows, matB columns
	mat_size_segment_id = shmget(mat_size_key, 5*sizeof(int), IPC_CREAT | 0666);
	if(mat_size_segment_id < 0)
    {
		printf("shmget error\n");
		exit(1);
	}

    // Attach shared memory
	mat_size_shared_memory = shmat(mat_size_segment_id, NULL, 0);
	if(mat_size_shared_memory == (int *) -1)
    {
		printf("shmat error\n");
		exit(1);
	}

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


	FILE *fp = fopen("input.txt", "r");
    // Read dimensions of matrix A and store them in shared memory
	fscanf(fp, "%d %d\n", &mat_size_shared_memory[0], &mat_size_shared_memory[1]);


	// MATRIX A - shmget and shmattach
	int mat_A_size = mat_size_shared_memory[0]*mat_size_shared_memory[1];
	matA_segment_id = shmget(matA_key, mat_A_size*sizeof(int), IPC_CREAT | 0666);

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

	// initialize contents of matrix A
	int index = 0;
	for (int j=0; j<mat_size_shared_memory[0]; j++) 
    {   //loop over rows of matrix A
		for (int k=0; k<mat_size_shared_memory[1]; k++) 
        {   //loop over columns
			fscanf(fp, "%d", &matA_shared_memory[index]);
			index++;
		}
	}

	fscanf(fp, "%d %d\n", &mat_size_shared_memory[2], &mat_size_shared_memory[3]);


	// MATRIX B - shmget and shmattach
	int mat_B_size = mat_size_shared_memory[2]*mat_size_shared_memory[3];
	matB_segment_id = shmget(matB_key, mat_B_size*sizeof(int), IPC_CREAT | 0666);

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

	if(matB_segment_id < 0)
    {
		printf("shmget error\n");
		exit(1);
	}

	matB_shared_memory = shmat(matB_segment_id, NULL, 0);

	if(matB_shared_memory == (int *) -1){
		printf("shmat error\n");
		exit(1);
	}

	// initialize contents of matrix B
	index = 0;
	for (int j=0; j<mat_size_shared_memory[2]; j++) 
    {   //loop over rows of matrix B
		for (int k=0; k<mat_size_shared_memory[3]; k++) 
        {   //loop over columns
			fscanf(fp, "%d", &matB_shared_memory[index]);
			index++;
		}
	}

	fclose(fp);	

	// Column of Matrix A must be equal to the row of Matrix B in matrix multiplication
	if (mat_size_shared_memory[1] != mat_size_shared_memory[2]) 
    {
		printf("Cannot perform matrix multiplication!\n");
		sleep(20);
		exit(1);
	}

    // Store the dimensions of matrices A and B
	int a_row = mat_size_shared_memory[0];
	int a_col = mat_size_shared_memory[1];
	int b_row = mat_size_shared_memory[2];
	int b_col = mat_size_shared_memory[3];
	

	// RESULTING MATRIX - shmget and shmattach
	int mat_result_size = a_row*b_col;
	mat_result_segment_id = shmget(mat_result_key, mat_result_size*sizeof(int), IPC_CREAT | 0666);

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


	// Compute the left half (and middle column if needed) of the resulting matrix product
	int a_index = 0;
	int mat_result_index = 0;
	int first_half = a_row/2;   //first half of the computation

	for (int k = 0; k <= first_half; k++) 
    {   // loop over rows in the first half
		int b_index = 0;

		for (int l = 0; l < b_col; l++) 
        {   // loop over columns in matrix B
			int sum = 0;        //sum of products for each element in the resulting matrix
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

	// Store current index in the shared memory
	mat_size_shared_memory[5] = mat_result_index;

	// Delay to allow shared data to be accessed by other processes
	sleep(100);

    // Detach shared memory
	shmdt(mat_size_shared_memory);
	shmdt(matA_shared_memory);
	shmdt(matB_shared_memory);
	shmdt(matB_shared_memory);
	shmdt(mat_result_shared_memory);

	shmctl(mat_size_segment_id, IPC_RMID, NULL);
	shmctl(matA_segment_id, IPC_RMID, NULL);
	shmctl(matB_segment_id, IPC_RMID, NULL);
	shmctl(matB_segment_id, IPC_RMID, NULL);
	shmctl(mat_result_segment_id, IPC_RMID, NULL);
}