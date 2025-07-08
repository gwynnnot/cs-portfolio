#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "graph.h"

//Implement your functions here

GRAPH *createGraph(int vertices)
{//	function for creating a graph
	GRAPH *G = (GRAPH *) malloc(sizeof(GRAPH));		// allocate memory for the graph

	// initialize the members of the structure
	G->num_vertices = vertices;
	G->matrix = (int **) malloc(sizeof(int *) * (vertices));

 	for (int u = 0; u < G->num_vertices; u++)
	{//	initializing matrix
		G->matrix[u] = (int *) malloc(sizeof(int) * (vertices));
		for (int v = 0; v < vertices; v++)
		{
			G->matrix[u][v] = 0;	// initialize each element in the adjacency matrix to 0
		}
	} 
	return G;	// return the newly created graph
}


void insertEdge(GRAPH *G, int u, int v)
{// function for plotting adjacent vertices
	G->matrix[u][v] = 1;	// insert edge in position u,v of the adjacency matrix
	G->matrix[v][u] = 1;	// insert edge in position v,u of the adjacency matrix
}


int *createVisited(GRAPH *G)
{//	function for the visited array
	int* visited = (int*) malloc(sizeof(int)*(G->num_vertices)); // allocate memory for array of visited vertices
	
	for (int i = 0; i < G->num_vertices; i++)
	{//	initializing each element of the visited array
		visited[i] = 0; // mark visited nodes
	}
	
	return visited;		// return array
}



/* STACK FUNCTIONS*/
NODE* createNode(int data)
{//	function for creating a new node
	NODE *new = (NODE *) malloc(sizeof(NODE)); // allocate memory

	new->value = data;	// initialize empty node with value 'data'
  	new->next = NULL;	// initialize next pointer to null	

  	return new; 		// return newly created node
}


STACK* createStack()
{//	function for creating an empty list
	STACK *list = (STACK *) malloc(sizeof(STACK)); 	// allocate memory
	list->head = NULL; 	// initialize head to NULL

	return list; 		// return the created list
}


int isEmpty(STACK *L)
{//	function for checking if the list is empty
	if (L->head == NULL)
		return 1;	// list is empty
	return 0;		// list is not empty
}


void push(STACK *L, NODE* node)
{//	function for inserting node at head
	node->next = L->head;	// next pointer of node points to the current head of the list
	L->head = node;			// this inserts the node before the head
}


int pop(STACK *L)
{//	function for deleting node at head
	NODE *todel = L->head;
	int data = todel->value;	// catch the value of the node to be deleted
	
	L->head = L->head->next;

	free(todel);	// delete the head node and deallocate memory

	return data;	// return the value of the deleted node

}

/* end of STACK FUNCTIONS */ 



void dfs(GRAPH *G, int start)
{//	function that implements a non-recursive DFS traversal
	int u,v;
	int *visited = createVisited(G);	// create visited array
	
	STACK *S = createStack();			// create stack
	
	// push first vertex in the stack
	push(S, createNode(start));		
	
	do {
		u = pop(S); 			// pop the element in the stack and store it in u
		if (visited[u] == 0)	
		{//	if u is not yet visited
			visited[u] = 1;		// mark it as visited 
			printf("%d ", u+1);	// print
		}

		v = G->num_vertices;	// initialize v
		while (v > 0) {
			if (G->matrix[u][v] == 1)
			{//	check each adjacent vertex of u
				if (visited[v] == 0)
				{//	if v is not yet visited
					push(S, createNode(v));	// push it in the stack
				}
			}
			v--;	// decrement
		}
	} while(!isEmpty(S)); 	// loop until stack is empty
}


void printMatrix(GRAPH *G)
{// function for printing the values of the adjacency matrix
    for (int u = 0; u < G->num_vertices; u++)
    {// iterate through rows
        for (int v = 0; v < G->num_vertices; v++)
        {// iterate through columns
            printf("%d\t", G->matrix[u][v]);	// print
        }
        printf("\n");
    }
}

void freeMatrix(GRAPH *G)
{// function for freeing each allocated memory
    for (int i = 0; i < G->num_vertices; i++)
    {
        free(G->matrix[i]);		// deallocate memory 
		G->matrix[i] = NULL;	// and set to null
    }   
}



int main() {
	char command;
	int vertices, lines, u, v;

	scanf("%d", &vertices);
	GRAPH *G = createGraph(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d", &u, &v);
				insertEdge(G, u-1, v-1); //there's a -1 since we use 0-indexing in the arrays
				printf("Successfully inserted edge %d %d\n", u, v);
				break;
			case '#':
				printf("\nDFS: ");
				dfs(G, 0); //0 is the initial value since we use 0-indexing (it still represents vertex 1)
				printf("\n");
				break;
			case 'p':
				printf("\nADJACENCY MATRIX: \n");
				printMatrix(G);
				break;
			case 'f':
				freeMatrix(G);
				break;
			case 'Q':
				freeMatrix(G);
				free(G);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
}
