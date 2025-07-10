/*
 * Author: MARY GWYNETH A. TOLENTINO
 * Section: B-5L
 * Program Description: A program that implements the Shortest Remaining Processing Time 
 * (SRPT) scheduling algorithm in a given list of processes from process.txt
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

/* Process Control Block (PCB) */
typedef struct PCB {
	int process_id;
	int arrival_time;
	int job_length;
	int wait_time;
	int run_time;
}PCB;

/* Singly-linked list of PCB */
typedef struct linked_list{
	PCB pcb;
	struct linked_list *next;
}linked_list;

/* Stores the processes */
linked_list *ready_queue = NULL;


/* Prints the details of the process */
void PrintPCB(PCB pcb){
	printf("\tProcess ID: %d, Arrival Time: %d, Job Length: %d, Wait Time: %d, Run Time: %d\n", pcb.process_id, pcb.arrival_time, pcb.job_length, pcb.wait_time, pcb.run_time);
}


/* Prints the processes in the ready queue */
void PrintReadyQueue(){
	linked_list *ptr = ready_queue;

	if (ptr!=NULL) 
		printf("\n\tPrinting Ready Queue:\n");

	while(ptr!=NULL){
		PrintPCB(ptr->pcb);		// print each process
		ptr = ptr->next;		// move to next process in queue
	}
}


/* 
 * Reads from process.txt
   * First line of the file is the process count
   * Succeeding lines are the <arrival_time> <job_length> values
   * Assume that the processes are sorted in ascending order by arrival time
 * Stores <arrival_time> to arrival_time array
 * Stores <job_length> to job_length array
 * Returns the process count
 */
int ReadProcesses(int *arrival_time, int *job_length){
	int arrival, length, pcnt;
	FILE *fp;

	fp = fopen("process.txt", "rw");
	
	if(fp != NULL)
	{
		fscanf(fp, "%d\n", &pcnt);		// read the first line as pcnt or number of processes

		for (int i = 0; i < pcnt; i++) 		
		{
			fscanf(fp, "%d %d\n", &arrival_time[i], &job_length[i]);	
		}

		fclose(fp);
	}
	return pcnt;	// return process count
}


/* 
 * Prints the terminated process
 * Removes the terminated process at the head of the queue
 */
void Dequeue(){	
	printf("\n\tThe following process already ended:\n");
	PrintPCB(ready_queue->pcb);			// print terminated process

	linked_list *temp = ready_queue;
	ready_queue = ready_queue->next;	// move to the next process in queue
	free(temp);							// free memory of terminated process
}


/* Inserts the process in the queue */
void Enqueue(int process_id, int arrival, int job_length){
	linked_list *new = (linked_list *) malloc(sizeof(linked_list));	

	// initialize PCB fields for the new process
	new->pcb.process_id = process_id;
	new->pcb.arrival_time = arrival;
	new->pcb.job_length = job_length;
	new->pcb.wait_time = 0;
	new->pcb.run_time = 0;

	// if ready queue is empty or the new process has a shorter remaining job time
	if ((ready_queue == NULL) || (ready_queue != NULL && (new->pcb.job_length - new->pcb.run_time) < (ready_queue->pcb.job_length - ready_queue->pcb.run_time))) 
	{ 	// insert at head
		new->next = ready_queue;
		ready_queue = new;
	} 
	else 
	{ 	// insert process in the correct position in the queue
		struct linked_list *temp = ready_queue;
		// check if it has a shorter remaining job time than the current head
		while (temp->next != NULL && (temp->next->pcb.job_length - temp->next->pcb.run_time) < (new->pcb.job_length - new->pcb.run_time)) 
		{
			temp = temp->next;		// traverse to find the correct position
		}

		new->next = temp->next;		// inset process in the queue
		temp->next = new;
	}
}


/*
 * Simulates processing of a single CPU cycle
 * Increases the run time of the currently executing process
   * Currently executing processs is the first process in the queue
 * Increases the wait time of the other processes in the queue
 * Checks if a process terminates (run time == job length)
 */
void Processing(){
	ready_queue->pcb.run_time++;				// increment run time of the current process

	linked_list *temp = ready_queue->next;
	while (temp != NULL) 
	{	// for all processes waiting in the queue
		temp->pcb.wait_time++;		// increment wait time
		temp = temp->next;
	}

	// if the current process completes (run_time == job_length)
	if (ready_queue->pcb.run_time == ready_queue->pcb.job_length) 
		Dequeue(); 			// remove it from the queue
}


/* 
 * Simulates the CPU scheduling
 * Checks the arrival of processes in a given cpu cycle
 * Updates the processes in the queue
 * Prints the processes in the ready queue
 */
void RunSimulation(int *arrival_time, int *job_length, int process_count){
	int i=0, cpu_cycles=1;
	
	while(1)
	{
		printf("\nCPU Cycle: %d\n", cpu_cycles);
		
		// check if a new process arrives in this cycle
		if (i < process_count && cpu_cycles == arrival_time[i])
		{
			Enqueue(i, arrival_time[i], job_length[i]);	// enqueue new process when it arrives
			i++;	// move to next process 
		}



		Processing();
		PrintReadyQueue();
		cpu_cycles++;
		if(ready_queue == NULL) break;
	}
}


int main(){	
	int arrival_time[MAX], job_length[MAX];
	int process_count = ReadProcesses(arrival_time, job_length);
	RunSimulation(arrival_time, job_length, process_count);
}