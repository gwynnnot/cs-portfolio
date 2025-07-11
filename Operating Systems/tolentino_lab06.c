/**
	Author: Mary Gwyneth A. Tolentino
	Description: Virtual Memory Simulation
 */

#include<stdio.h>
#include <stdlib.h>

// TLB data structure
typedef struct TLBnode{
	int pageNum;
	int frameNumber;
	struct TLBnode *next;
}TLB;

TLB *tlb_head = NULL;


//initialize an empty page table
//page table is always size 256
void initializePageTable(int pageTable[]){
	int i;
	for(i=0;i<256;i+=1){
		pageTable[i] = -1;
	}
}

int updateTLB(int pNum, int fNum, int count, struct TLBnode **tlb_head) 
{
    TLB *new = (TLB *) malloc(sizeof(TLB));
    new->pageNum = pNum;
    new->frameNumber = fNum;
    new->next = NULL;

    TLB *ptr = (*tlb_head);
    if (ptr == NULL) 
	{
        (*tlb_head) = new;
        count++;
    } 
	else 
	{	// Append to tail
        TLB *temp = (*tlb_head);
        while (temp->next) 
		{
            temp = temp->next;
        }
        temp->next = new;
        count++;

        // If TLB is full, TLB_SIZE = 16
        if (count > 16) 
		{
            count--;
            temp = (*tlb_head);
            (*tlb_head) = (*tlb_head)->next;
            free(temp); //remove the oldest page (first added page)
        }
    }
    
    return count;
}

//main
int main(){
	int num,i,temp,pnum,poff,val,next_free_frame,physical_address,virtual_address,TLB_count=0; //Declared here are all the variables
	FILE *fp, *bp, *fpp;				 //you need. You can add other variables
	char physicalMemory[256][256];		 //you think are necessary.
	int pageTable[256];

	int PAGE_SIZE = 256;

	fp = fopen("addresses.txt","r"); //addresses to convert
	bp = fopen("BACKING_STORE.bin","rb"); //backing store

	initializePageTable(pageTable);

	if(fp!=NULL && bp!=NULL){
		fpp = fopen("answers.txt","w"); //you will put your answers here

		fscanf(fp, "%d", &num);
        for (i = 0; i < num; i++) {
            fscanf(fp, "%d", &virtual_address);
            int fnum;
        
            // Extract page number and offset
            pnum = virtual_address >> 8;
            poff = virtual_address & 255;

            // Check for TLB hit
            temp = 0;
            TLB *ptr = tlb_head;
            while (ptr != NULL) 
			{
                if (ptr->pageNum == pnum) 
				{
                    temp = 1;
                    fnum = ptr->frameNumber; // TLB hit
                    break;
                }
                ptr = ptr->next;
            }

            if (temp == 0) 
			{ // TLB miss
                if (pageTable[pnum] == -1) 
				{ 	// Page fault
                    fseek(bp, pnum * PAGE_SIZE, SEEK_SET);  //seek to the correct position in the backing store

                    // Copy the page into physical memory
                    for (int j = 0; j < PAGE_SIZE; j++) {
                        fread(&physicalMemory[next_free_frame][j], sizeof(char), 1, bp);
                    }

                    // Update page table and TLB
                    pageTable[pnum] = next_free_frame;
                    TLB_count = updateTLB(pnum, next_free_frame, TLB_count, &tlb_head);
                    fnum = next_free_frame;
                    next_free_frame++;
                } 
				else 
				{
                    fnum = pageTable[pnum]; //retrieve from page table
                    TLB_count = updateTLB(pnum, fnum, TLB_count, &tlb_head);    //update TLB
                }
            }

            // Calculate physical address and get the value
            val = physicalMemory[fnum][poff];
            physical_address = (fnum * PAGE_SIZE) + poff;

            // Output to file
            fprintf(fpp, "Virtual address: %d, PageNum: %d, PageOff: %d, Physical address: %d, Value: %d\n", 
                    virtual_address, pnum, poff, physical_address, val);
        }

		fclose(fp);
		fclose(bp);
		fclose(fpp);
	}


}
