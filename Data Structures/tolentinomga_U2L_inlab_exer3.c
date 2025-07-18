#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

// a recursive subroutine to display the BST in tree mode
void showTreeHelper(BST_NODE* node, int tabs){

	if(!node) return; // node is null, do nothing
	showTreeHelper(node->right, tabs + 1);
	for(int i=0; i<tabs; i++) printf("\t");
	printf("%d(%d)\n", node->key, node->height);
	showTreeHelper(node->left, tabs + 1);

}


void showTree(BST* B){
	showTreeHelper(B->root, 0);
}



int main(){

	char command;
	int key, result;

	BST *B = createBST(100);
	BST_NODE* node;
	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d\n", key);
				insert(B, createBSTNode(key, NULL, NULL, NULL));
				break;
			case '?':
				scanf(" %d", &key);
				printf("Searching node with key: %d. Location: %p\n", key, search(B, key));
				// (nil) means NULL pointer
				break;
			case 'p':
				printf("Tree (rotated +90 degrees): \n");
				showTree(B);
				printf("\n");
				break;
			case 'E':
				printf("BST %s empty.\n", isEmpty(B)?"is":"is not");
				break;
			case 'F':
				printf("BST %s full.\n", isFull(B)?"is":"is not");
				break;
			/* for the postlab, uncomment this
			case '<':
				printf("Pre-order Traversal: ");
				preorderWalk(B);
				printf("\n");
				break;
			case '>':
				printf("Post-order Traversal: ");
				postorderWalk(B);
				printf("\n");
				break;
			case '/':
				printf("In-order Traversal: ");
				inorderWalk(B);
				printf("\n");
				break;
			*/
			case 'Q':
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}

	return 0;
}


BST_NODE* createBSTNode(int key, BST_NODE* L, BST_NODE* R, BST_NODE* P)
{
	BST_NODE *new = (BST_NODE*) malloc(sizeof(BST_NODE));

	new->left = new->right = new->parent = NULL;
	new->key = key;

	return (new);
}

BST* createBST(int max){
	BST *new = (BST*) malloc(sizeof(BST));
	
	new->root = NULL; 
	new->maxSize = 100;
	new->size++;
	return (new);
}


int isEmpty(BST* B){
	if (B->root == NULL);
		return 1;
	return 0;
}


int isFull(BST* B){
	if (B->size > B->maxSize)
		return 1;
	return 0;
}


void insert(BST* B, BST_NODE* node)
{	
	if (isFull(B))	printf("The tree is full!");
	else
	{
		BST_NODE *new = B->root;

		if (new == NULL)
			new = node;
		else
		{
			BST_NODE* temp;

			while (new != NULL) 
			{
				temp = new; 
				if (node->key < new->key)
					new = new->left;
				else
					new = new->right;
			} 

			if (node->key < temp->key)
				temp->left = node;
			else 
				temp->right = node;
			node->parent = temp; 
		}
	}

}


BST_NODE* search(BST* B, int key){
	if (isEmpty(B))	
		return NULL;
	else
	{
		BST_NODE *temp = B->root;

		while(temp!=NULL && temp->key!=key){
			if(key < temp->key) {
				temp = temp->left;
			}
			else{
				temp = temp->right;
			}
		}
		return (temp);
	}

}



void preorderWalk(BST* B);
void inorderWalk(BST* B);
void postorderWalk(BST* B);

