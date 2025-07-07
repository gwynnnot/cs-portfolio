#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

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
			case '-':
				scanf("%d", &key);
				printf("Removing node with key: %d\n", key);
				delete(B, key); // result is unused. print if u want
				break;
			case '?':
				scanf("%d", &key);
				printf("Searching node with key: %d. Location: %p\n", key, search(B, key));
				// (nil) means NULL pointer
				break;
			case 'p':
				printf("Tree (rotated +90 degrees): \n");
				showTree(B);
				printf("\n");
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
			case 'm':
				node = minimum(B->root);
				if(node) printf("Minimum value: %d\n", node->key);
				else printf("(BST empty)\n");
				break;
			case 'M':
				node = maximum(B->root);
				if(node) printf("Maximum value: %d\n", node->key);
				else printf("(BST empty)\n");
				break;
			case 'E':
				printf("BST %s empty.\n", isEmpty(B)?"is":"is not");
				break;
			case 'F':
				printf("BST %s full.\n", isFull(B)?"is":"is not");
				break;
			case 'C':
				printf("Removing all contents.\n");
				clear(B);
				break;
            case '[':
				scanf("%d", &key);
				node = search(B, key);
				if(!node){
					printf("%d not found\n", key);
				}else{
					node = predecessor(node);
					if(node)printf("Predecessor of %d is %d.\n", key, node->key);
					else printf("No predecessor for %d\n", key);
				}
				break;
			case ']':
				scanf("%d", &key);
				node = search(B, key);
				if(!node){
					printf("%d not found\n", key);
				}else{
					node = successor(node);
					if(node)printf("Successor of %d is %d.\n", key, node->key);
					else printf("No successor for %d\n", key);
				}
				break;
			case 'Q':
				clear(B);
				free(B);
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
		BST_NODE *temp;

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

/*
** function: minimum
** requirements:
    a non-null BST_NODE pointer
** results:
    finds the leftmost node of the subtree rooted at node n and returns its node pointer if found, 
        otherwise, return `NULL`
*/
BST_NODE* minimum(BST_NODE* n)
{
	BST_NODE *temp = n;
	if (n != NULL)
	{
		while (temp->left != NULL)
		{
			temp = temp->left;
		}
	}
	return temp;
}

/*
** function: maximum
** requirements:
    a non-null BST_NODE pointer
** results:
    finds the rightmost node of the subtree rooted at node n and returns its node pointer if found, 
        otherwise, return `NULL`
*/
BST_NODE* maximum(BST_NODE* n)
{
	BST_NODE *temp = n;
	if (n != NULL)
	{
		while (temp->right != NULL)	// traverse until right child is null
		{
			temp = temp->right;
		}
	}
	return temp;
}

/*
** function: remove
** requirements:
    a non-null BST pointer
    a non-empty BST
    an integer `key`
** results:
    finds `key` and delete's it node from the BST `B`
    if found, delete then, return key
    otherwise, return 0
*/
int delete(BST* B, int key)
{
	BST_NODE *temp = B->root;
	BST_NODE *todel;

	while (temp->key != key)
	{
		if(key <= temp->key)
		{
			temp = temp->left;
			if(temp == NULL)
			{
				printf("Node to delete is not found.\n");
				return 1;
			}
		}
		else
		{
			temp = temp->right;
			if(temp == NULL)
			{
				printf("Node to delete is not found.\n");
				return 1;
			}
		}
	}
	
	//case 1: no child
	if (temp->left == NULL && temp->right == NULL)
	{	
		if (temp == B->root)
		{//root
			free(temp);
			B->root = NULL;
		}
		else
		{//left child
			todel = temp->parent;
			if (temp->key <= todel->key)
			{
				free(todel->left);
				temp->parent->left = NULL;
			}
			free(todel->right);
			todel->parent->right = NULL;	
        }
	}
	
	//case 2: node has 1 child
	else if ((temp->left != NULL && temp->right == NULL) || (temp->left == NULL && temp->right != NULL))
	{
		todel = temp->parent;
		if(temp->left != NULL)
		{	//if the child is on the left of the root
			temp = temp->left;
			free(todel);
			temp->parent = NULL;
			B->root = temp;
		}
		else
		{	//if the child is on the right of the root
			temp = temp->right;
			free(todel);
			temp->parent = NULL;
			B->root = temp;	
		}
	}

	// case 3: node has 2 children
	else
	{	
		todel = temp->right;
		while(todel->left!=NULL)	//find the successor
			todel = todel->left;

		temp->key = todel->key;		//copy the value of the successor

		if(todel->left==NULL && todel->right==NULL)
		{	//if successor has no children
			if(todel->parent == temp)
				temp->right = NULL;
			else
				todel->parent->left = NULL;
			free(todel);
		}
		else
		{
			if(todel->right!=NULL)
			{	//if the successor has a child (check right cause successor is already the leftmost)
				if(todel->parent == temp)
                {
					temp->right = todel->right;
					todel->right->parent = temp;
				}
				else
                {
					todel->parent->left = todel->right;
					todel->right->parent = todel->parent;
				}
				free(todel);
			}
		}

	}	

	B->size--;
	return key;
}

/*
** function: predecessor
** requirements:
    a non-null BST_NODE pointer
** results:
    returns the node pointer of this node's predecessor, if it exists
    otherwis, return `NULL`
*/
BST_NODE* predecessor(BST_NODE* node)
{
    BST_NODE *temp = node->left;
	if (node->left != NULL)
	{
		while (temp->right != NULL)
		{
			temp = temp->right;
		}
	}
	return temp;
}

/*
** function: successor
** requirements:
    a non-null BST_NODE pointer
** results:
    returns the node pointer of this node's successor, if it exists
    otherwis, return `NULL`
*/
BST_NODE* successor(BST_NODE* node)
{
    BST_NODE *temp = node->right;
	if (node->right != NULL)
	{
		while (temp->left != NULL)
		{
			temp = temp->left;
		}
	}
	return temp;
}

/*
** function: clear
** requirements:
    a non-null BST pointer
** results:
    removes all data items in the BST
*/
void clear(BST* B)
{
	BST_NODE *node = B->root;
	if(B->root == NULL)
		return;
	free(node);
	B->root = NULL;
    B->size = 0;
}