#include <stdio.h>
#include <stdlib.h>
//#include "list.h"
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

void insertEdge(GRAPH *G, int u, int v, int w)
{// function for plotting adjacent vertices
	G->matrix[u][v] = w;	// insert edge in position u,v of the adjacency matrix
}

int *createVisited(GRAPH *G)
{//	function for the visited array
	int* visited = (int*) malloc(sizeof(int)*(G->num_vertices)); // allocate memory for visited array of visited vertices
	
	for (int i = 0; i < G->num_vertices; i++)
	{//	initializing each element of the visited array
		visited[i] = 0; // not visited yet
	}
	
	return visited;		// return visited array
}


int *createDistance(GRAPH *G)
{//	function for the distance array
	int* distance = (int*)malloc(sizeof(int)*(G->num_vertices));	// allocate memory for distance array 
	
    for (int i = 0; i < G->num_vertices; i++)
	{//	initializing each element of distance array
		distance[i] = 99999; // maximum distance possible
	}
	
	return distance;    // return distance array
}


int *createParent(GRAPH *G)
{//	function for the parent array
	int* parent = (int*)malloc(sizeof(int)*(G->num_vertices)); 		// allocate memory for parent array
	
    for (int i = 0; i < G->num_vertices; i++)
	{//	initializing each element of parent array
		parent[i] = -1; // no parent yet
	}
	
	return parent;      // return dijkstra parent array
}


void dijkstra(GRAPH *G, int source, int target)
{//	fuction for implementing dijkstra's algorithm to find the shortest path from a source to a target
	int *visited = createVisited(G); 	// create array of visited vertices
	int *distance = createDistance(G);	// create array of distances of the vertices
	int *parent = createParent(G); 		// create array of parent of the vertices	
	int n = G->num_vertices; 			// get number of vertices
	
	distance[source] = 0; 	// set the distance of the source vertex to 0
	
    while(1)
	{
		int u = -1; 		// set initial value of u to -1
		int min; 			// create min value for distance

		for (int i = 0; i < G->num_vertices; i++)
		{//	loops thru the number of vertices	
			if (visited[i] == 0 && distance[i] != 99999)
            {// check if it is not yet visited and if its distance is not 99999
				if (u == -1)
                { 
					u = i;  // set value of u to i
					min = distance[i];  // set minimum distance 
				}
                else if (distance[i] <= min)
                {// check if distance is the minimum
					u = i;
					min = distance[i];
				}
			}
		}


		visited[u] = 1;     // visits u
		if (u == -1)   break;

		for (int v = 0; v < n; v++)
        {// checks the row u in the 2d matrix
			if (G->matrix[u][v] != 0)
            {// checks all adjacent vertex of the u
				if (visited[v] == 0)
                {// check if adjacent vertex is not yet visited
					int alt_distance = ((distance[u]) + (G->matrix[u][v])); // compute for alternative distance
					if (distance[v] > alt_distance)
                    {
						distance[v] = alt_distance; // update the distance of v
						parent[v] = u;              // set u as the parent of v
					}
				}
			}
		}
	}
	

// FOR CHECKING
	// printf("visited:	");
	// for (int a = 0; a < n; a++)
	// {
	// 	printf("%d ", visited[a]);
	// }	printf("\n");

	// printf("distance:	");
	// for (int a = 0; a < n; a++)
	// {
	// 	printf("%d	", distance[a]);
	// }	printf("\n");

	// printf("parent:	");
	// for (int a = 0; a < n; a++)
	// {
	//   	printf("%d ", parent[a]);
	// }	printf("\n");


	int* path = (int*)malloc(sizeof(int)*(G->num_vertices)); // allocate memory for path array
	for (int i = 0; i < G->num_vertices; i++)
    {// initializing each element of path array
		path[i] = -1; 
	}
	 
	if (visited[target] == 0)
    {// check if target is not yet visited
		printf("PATH FROM %d to %d: ", source + 1, target + 1); 
		printf("IMPOSSIBLE!");  // path is impossible
		printf("\nDISTANCE FROM %d to %d: -1\n", source + 1, target + 1); // print -1 as distance
	}
    
    else
    {
		int tar = target;
		int c = 0;
		while(tar != -1)
        {// while loop for storing target and parent in path
			int par = parent[tar];
			path[c] = tar + 1;
			tar = par;
			c++;
		}

	// FOR CHECKING
		// printf("path: ");
	 	// for (int a = 0; a < n; a++)
		// {
	 	// 	printf("%d ", path[a]);
	 	// }	printf("\n");

		printf("PATH FROM %d to %d: ", source + 1, target + 1);
		for (int j = n-1; j >= 0; j--)
        {
			if (path[j] != -1)
            {// print the path in reverse
			    printf("%d ", path[j]);
			}
		}
		
		printf("\nDISTANCE FROM %d to %d: ", source + 1, target + 1);
		printf("%d\n", distance[target]); // print the distance of the target
	}

	free(path);
}

void printMatrix(GRAPH *G)
{// function for printing the values of the adjacency matrix
    for (int u = 0; u < G->num_vertices; u++)
    {// iterate through rows
        for (int v = 0; v < G->num_vertices; v++)
        {// iterate through columns
            printf("%d\t", G->matrix[u][v]);	// print value
        }
        printf("\n");
    }	printf("\n");
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
	int vertices, lines, u, v, w, source, target;

	scanf("%d", &vertices);
	GRAPH *G = createGraph(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d %d", &u, &v, &w);
				insertEdge(G, u-1, v-1, w); //there's a -1 since we use 0-indexing in the arrays
				printf("Successfully inserted edge %d %d\n", u, v);
				break;
			case '#':
				scanf(" %d %d", &source, &target);
				dijkstra(G, source-1, target-1);
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