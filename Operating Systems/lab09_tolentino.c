/* 2021-02990
 * Author: Mary Gwyneth A. Tolentino
 * Section: B-5L
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>		// time()
#include <math.h>		// srand() and ran()
#include <pthread.h>	// PTHREADS
#include <semaphore.h>	// SEMAPHORES
#include <unistd.h>
#define N 5

// This method will be performed by each philosopher
void * Philosophize(void * id);

// Chopsticks: Shared resources
sem_t chopstick[N];
// IF YOU DO NOT WANT TO USE SEMAPHORES, YOU CAN USE MUTEXES

int main()
{
	int i;

	// Create 5 PHILOSOPHER
	pthread_t philo[N];
  	int *ids = (int *) malloc(sizeof(int) * N);

	// Initialize Semaphores
	for(i=0; i<N; i++){
		sem_init(&chopstick[i], 0, 1);
	}

	// CREATE PHILOSOPHER threads
	for(i=0; i<N; i++){
    ids[i] = i;
		pthread_create(&philo[i], NULL, Philosophize, (void *) &ids[i]);
	}

	// JOIN PHILOSOPHER threads
	for(i=0; i<N; i++){
		pthread_join(philo[i], NULL);
	}

	return 0;
}

void * Philosophize(void * id){
    int ID = *((int *) id);

    while(1){

        // 1. THINK for a while
        int thinking = rand()%10;
        printf("Philosopher %d is thinking...\n", ID);
        sleep(thinking);
		
		// PICK-UP chopsticks in an asymmetrical order to prevent deadlock

        // 2. PICK-UP left chopstick 
        if (ID % 2 == 0)
		{	// Even philosophers pick up left chopstick first
            sem_wait(&chopstick[ID]);  
            printf("Philosopher %d picked up his left chopstick!\n", ID);
        } else
		{	// Odd philosophers pick up right chopstick first
            sem_wait(&chopstick[(ID + 1) % N]);  
            printf("Philosopher %d picked up his right chopstick!\n", ID);
        }

        // 3. PICK-UP right chopstick 
        if (ID % 2 == 0) 
		{	// Even philosophers pick up right chopstick next 
            sem_wait(&chopstick[(ID + 1) % N]);  
            printf("Philosopher %d picked up his right chopstick!\n", ID);
        } else 
		{	// Odd philosophers pick up left chopstick next
            sem_wait(&chopstick[ID]);  
            printf("Philosopher %d picked up his left chopstick!\n", ID);
        }

        // 4. EAT for a while
        int eating = rand()%10;
        printf("Philosopher %d is eating for %d seconds...\n", ID, eating);
        sleep(eating);

        // 5. RELEASE left chopstick 
        if (ID % 2 == 0) 
		{	// Even philosophers release left chopstick first
            sem_post(&chopstick[ID]);  
            printf("Philosopher %d released his left chopstick!\n", ID);
        } else 
		{	// Odd philosophers release right chopstick first
            sem_post(&chopstick[(ID + 1) % N]);  
            printf("Philosopher %d released his right chopstick!\n", ID);
        }

        // 6. RELEASE right chopstick
        if (ID % 2 == 0) 
		{	// Even philosophers release right chopstick next
            sem_post(&chopstick[(ID + 1) % N]);  
            printf("Philosopher %d released his right chopstick!\n", ID);
        } else 
		{	// Odd philosophers release left chopstick next
            sem_post(&chopstick[ID]);  
            printf("Philosopher %d released his left chopstick!\n", ID);
        }

        printf("Philosopher %d is done eating!\n", ID);
    }

}