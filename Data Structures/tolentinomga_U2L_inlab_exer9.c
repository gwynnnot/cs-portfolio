/*
 * Name: Mary Gwyneth A. Tolentino 
 * Lab Section: U-2L 
 * Program Description: A program that implements a hash table with double hashing
*/

#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>		//for strcmp and strcpy

//Function that prints the data of the hash table
void printTable(HASH_TABLE_PTR H){
	if(isEmpty(H)) {
		printf("*empty\n");
		return;
	}

	for(int index=0; index<H->tableSize; index++){
		printf("Cell#%d: ", index);
		if(H->list[index]){
			printf("%s\n", H->list[index]);
		}else{
			printf("*empty*\n");
		}
	}
}

//Create your own hash functions

int computeKey(STRING key)
{ 	// computes a hash key based on the ASCII values of characters in the key
	int ascii = 0;

	for (int i = 0; i < strlen(key); i++)
	{	// iterate through each character of the string
		if ((int)key[i] % 2 == 0)	
			// check if the ASCII value of the character at index i is an even number
			ascii = ascii + (int)key[i];
	}

	return ascii;
}

int firstHash(STRING key, int tableSize)
{	// first hash function
	return (computeKey(key) % tableSize);
}

int secondHash(STRING key)
{	// second hash function
	return (17 + computeKey(key) % strlen(key));
}


//Insert the implementations of the functions found in the header file

HASH_TABLE_PTR createHashTable(int tableSize)
{	// creates a hash table
	HASH_TABLE_PTR H = (HASH_TABLE_PTR) malloc(sizeof(HASH_TABLE));
	// initializes fields
	H->size = 0;
	H->tableSize = tableSize;
	// initializes array of strings
	H->list = (STRING_ARRAY_PTR) malloc(sizeof(STRING) * tableSize);

	for (int i = 0; i < tableSize; i++)
	{	// all slots in the list array are initialized to NULL
		H->list[i] = NULL;
	}

	return H;	// returns the created hash table
}


int isEmpty(HASH_TABLE_PTR H)
{	// checks if the hash table is full
	if (H != NULL && H->size == 0)	
		return 1;		// is empty
	return 0;	// is not yet empty
	
}

int isFull(HASH_TABLE_PTR H)
{	// checks if the hash table is full
	if (H != NULL && H->size >= H->tableSize)
		return 1;		// is full
	return 0;	// is not yet full
}

void put(HASH_TABLE_PTR H, STRING key, STRING data) 
{	// inserts data into the hash table
	int h1 = firstHash(key, H->tableSize);
    int h2 = secondHash(key);
    int index;

    if (isFull(H) == 0)
	{
        for (int i = 0; i < H->tableSize; i++)
		{	// finds an appropriate slot for inserting the data
            index = (h1 + i * h2) % (H->tableSize);

            if (H->list[index] == NULL) 
			{	// check if a slot is empty
               	H->list[index] = (STRING) malloc(sizeof(STRING) * (strlen(key)));
                strcpy(H->list[index], data); // copy data into the allocated memory at the index
                H->size++;	// increment number of data elements
                
				break;		// exit loop once insertion is done
            }
        }
    }
	
    else printf("Hash table is full!\n");
}


STRING find(HASH_TABLE_PTR H, STRING key, STRING data)
{	// searches for data in the hash table
	int h1 = firstHash(key, H->tableSize);
	int h2 = secondHash(key);
	int index;

	if (isEmpty(H) == 0)
	{
		for (int i = 0; i < H->tableSize; i++)
		{
			index = (h1 + i * h2) % (H->tableSize);

			if (H->list[index] == NULL)
				// if slot is empty, the data is not present in the hash table
				return NULL;
			else if (strcmp(H->list[index], data) == 0)
				// if found, return string data
				return H->list[index];
		}
	}

	else printf("Hash table is empty.");
	return NULL;
}

STRING erase(HASH_TABLE_PTR H, STRING key, STRING data)
{	// removes data from the hash table
	int h1 = firstHash(key, H->tableSize);
	int h2 = secondHash(key);
	int index;

	if (isEmpty(H) == 0)
	{
		for (int i = 0; i < H->tableSize; i++)
		{
			index = (h1 + i * h2) % (H->tableSize);
			if (H->list[index] == NULL)		
				return NULL;
			else if(strcmp(H->list[index], data) == 0)
			{	// if found, delete the node
				free(H->list[index]);
				H->list[index] = NULL;
				H->size--;		// decrement current number of data elements

				return data;	// return the data
			}	
		}
	}

	else printf("Hash table is empty.");
	return NULL;
}


void destroy(HASH_TABLE_PTR H)
{	// deallocates memory and clears the hash table
  	for (int i = 0; i < H->tableSize; i++)
	{	
        if (H->list[i] != NULL) 
		{	// check if current slot in the hash table is not empty
            free(H->list[i]);	// delete
            H->list[i] = NULL;	// free allocated memory
        }
    }

	H->size = 0;
}


int main(){

	char command;
	STRING key;
	STRING data;
	STRING result;

	uint tsize;
	HASH_TABLE_PTR H;
	
	// get table size then maxsize
	scanf("%d\n", &tsize); 
	H = createHashTable(tsize);

	// assume max key size is 20
	key = (STRING)malloc(sizeof(char)*20);
	key[0] = '\0';
	// assume max data size is 100
	data = (STRING)malloc(sizeof(char)*100);
	data[0] = '\0';

	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf(" k:%s d:%s", key, data);
				printf("Inserting data %s with key %s\n", data, key);
				put(H, key, data);
				break;
			case '-':
				scanf(" %s", key);
				printf("Deleting data with key %s\n", key);
				result = erase(H, key, data); 
				// result is unused. print if u want
				break;
			case '?':
				scanf(" k:%s d:%s", key, data);
				printf("Searching data with key: %s. Location: %p\n", key, find(H, key, data));
				// (nil) means NULL pointer
				break;
			case 'p':
				printf("Hash Table: \n");
				printTable(H);
				printf("\n");
				break;
			case 'E':
				printf("Hash table %s empty.\n", isEmpty(H)?"is":"is not");
				break;
			case 'F':
				printf("Hash table %s full.\n", isFull(H)?"is":"is not");
				break;
			case 'C':
				printf("Deleting all contents.\n");
				destroy(H);
				break;
			case 'Q':
				free(key); free(data);
				destroy(H); // ensure deletion
				free(H->list);
				free(H);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
	
	return 0;
}
