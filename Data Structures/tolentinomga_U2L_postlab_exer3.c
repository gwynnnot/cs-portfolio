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

	// initialize values for a new node
    new->key = key; 	
    new->left = L;		
    new->right = R;		
    new->parent = P;	
    new->height = 0; 	// initialize height to 0

    return (new);	// return a pointer to the new node
}

BST* createBST(int max)
{
	BST *new = (BST*) malloc(sizeof(BST));
	
	new->root = NULL; 	// set to null initially
	new->maxSize = max;	// set to the provided 'max' value
	new->size = 0;		// initialize size of the BST to 0 

	return (new);	// return a pointer to the new BST
}


int isEmpty(BST* B)
{
	if (B == NULL || B->root == NULL)
        return 1;	// BST is empty
	return 0;	// not empty
}


int isFull(BST* B)
{
	if (B == NULL) 
        return 0;
	else if (B->size >= B->maxSize)
		return 1;	// BST is full
	return 0;
}


void insert(BST* B, BST_NODE* node)
{	
	if (isFull(B))	printf("The tree is full!");
	else
	{
		if (B -> root == NULL) {// BST is empty
			B -> root = node;	// new node becomes the root
			B -> size = 1;
			return;
		}

		BST_NODE *new = B->root;
		BST_NODE* temp;

		while (new != NULL) 
		{
			temp = new; 	
			if (node->key < new->key)
				new = new->left;	// move to the left child if new node is smaller
			else
				new = new->right;	// move to the left child if new node is larger
		} 

		B->size++;	// increment the size of the true
		node->parent = temp; // set the parent of the new node

		if (node->key < temp->key)
			temp->left = node;	// node becomes the left child
		else 
			temp->right = node;	// node becomes the right child
		
	}
	
	// update height of the ancestors starting from the newly inserted node
    while (node != NULL) {
        int leftHeight, rightHeight;

		// height of the left subtree
        if (node->left != NULL) 
            leftHeight = node->left->height;
        else 
            leftHeight = -1;	// height of an empty tree is -1
        
        
		// height of the right subtree
        if (node->right != NULL) 
            rightHeight = node -> right -> height;
        else 
            rightHeight = -1;	
        
		
		// update height of the current node
        // node->height = max(leftHeight, rightHeight) + 1
		if (leftHeight > rightHeight) 
            node -> height = 1 + leftHeight;
        else 
            node -> height = 1 + rightHeight;

        node = node -> parent;	// move to the parent node
	}
	
}


BST_NODE* search(BST* B, int key)
{
	if (isEmpty(B))	
		return NULL;
	else
	{
		BST_NODE *temp = B->root;

		while (temp != NULL  && temp->key != key) {
			// if key is smaller
			if (key < temp -> key)
				temp = temp -> left;	// move to the left child 
			else // if key is larger
				temp = temp -> right;	// move to the right child 
		}
		return temp;	// return found node
	}
}


// (Root, Left, Right) manner
void preorderWalk(BST *B)
{
	if (isEmpty(B))	
	{
		printf("The tree is empty");
		return;
	}	

	BST_NODE *BSTArray[20]; // stack to store nodes during traversal
	int BSTArrayCounter = -1;
	
	BST_NODE *ptr = B->root; // initialize pointer to the root of the BST in order to traverse

	while (ptr != NULL || BSTArrayCounter != -1) // traverse until stack is empty
	{ 
		if (ptr != NULL) // check if current node is not null
		{
			printf("%d ", ptr->key); // print the key whenever we visit a node

			BSTArrayCounter++; // increment the counter
			BSTArray[BSTArrayCounter] = ptr; // push current node on the stack

			ptr = ptr->left; // move to the left child
		}
		else
		{
			ptr = BSTArray[BSTArrayCounter]; // pop the current top of the stack
			BSTArrayCounter--; // decrement the counter 

			ptr = ptr->right; // move to the right child
		}	
	}
}


// (Left, Right, Root) manner
void postorderWalk(BST *B)
{
	if (isEmpty(B))	
	{
		printf("The tree is empty");
		return;
	}	

	BST_NODE *BSTArray[20]; 
	int BSTArrayCounter = -1;
	
	BST_NODE *ptr = B->root;// initialize pointer to the root of the BST
	BST_NODE *temp = NULL;	// temp pointer to keep track of the last visited node

	while (ptr != NULL || BSTArrayCounter != -1)
	{
		if (ptr != NULL)
		{
			BSTArrayCounter++;	// increment the counter
			BSTArray[BSTArrayCounter] = ptr;	// push current node onto the stack

			ptr = ptr->left; // move to the left child
		}
		else
		{
			ptr = BSTArray[BSTArrayCounter]; // set ptr to the current top of the stack

			if (ptr->right == NULL || ptr->right == temp)
			{
				printf("%d ", ptr->key); // print key

				BSTArrayCounter--; // decrement the counter

				temp = ptr; // set temp to the current node
				ptr = NULL;	// set ptr to null to move up the tree
			}
			else 
				ptr = ptr->right; // traverse to the right child of the node
		}	
	}
}


// (Left, Root, Right) manner
void inorderWalk(BST *B)
{
	if (isEmpty(B))
    {
    	printf("The tree is empty");
        return;
    }
	
	BST_NODE *BSTArray[20]; 
	int BSTArrayCounter = -1;
	
	BST_NODE *ptr = B->root;	// initialize pointer to the root of the BST

	while (ptr != NULL || BSTArrayCounter != -1)
	{
		if (ptr != NULL)
		{
			BSTArrayCounter++;	// increment the counter
			BSTArray[BSTArrayCounter] = ptr;	// push current node on the stack


			ptr = ptr->left;	// move to the left child
		}
		else
		{
			ptr = BSTArray[BSTArrayCounter];	// pop a node from the stack
			BSTArrayCounter--;	// decrement the counter

			// print node only before we traverse to the right node
			printf("%d ", ptr->key);

			ptr = ptr->right;	// move to the right child
		}	
	}
}