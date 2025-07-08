/* ********************************************************* *
 * BST.c                                                     *
 *                                                           *
 * Contains the function definitions of all functions        *
 *    declared in BST.h.                                     *
 *                                                           *
 * !!! DO NOT EDIT LINES 11-28 !!!                           *
 *                                                           *
 * ********************************************************* */
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

/***********************************************************************/
/* Copy your previous function definitions for the functions in BST.h. */
/* PASTE THEM BELOW THIS COMMENT.                                      */
/***********************************************************************/

//your implementation for the functions in BST.h below !!!


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
            rightHeight = node->right->height;
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

void clear(BST* B)
{
	BST_NODE *node = B->root;
	if(B->root == NULL)
		return;
	free(node);
	B->root = NULL;;
}