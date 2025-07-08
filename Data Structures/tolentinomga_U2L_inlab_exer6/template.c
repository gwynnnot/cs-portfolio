/* ********************************************************* *
 * template.c                                                *
 *                                                           *
 * Template C Source File for AVL Insert.                    *
 *                                                           *
 * !!! DO NOT EDIT THE CONTENTS OF THE MAIN FUNCTION !!!     *
 *                                                           *
 * ********************************************************* */
#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

AVL_NODE * createAVLNode(int key){
    return createBSTNode(key, NULL, NULL, NULL);
}

AVL * createAVL(int max){
    return createBST(max);
}

/**** PUT YOUR FUNCTIONS HERE ******************************/


/*
** function: heightOf
** requirements:
    a non-null node pointer
** results:
    returns -1 if node is NULL
    otherwirse, return the height of node
*/
int heightOf(AVL_NODE * node)
{
	if (node != NULL)
		return node->height;
	return -1;
}


void updateHeight(AVL_NODE* node)   // modified and copied from insert of BST.c
{
    int leftHeight, rightHeight;
    if (node != NULL)
    {
        leftHeight = heightOf(node->left);
        rightHeight = heightOf(node->right);

        // check if node has both a left child and a right child
        // add 1 to the height of the child with a greater height
		if (leftHeight > rightHeight) 
            node->height = 1 + leftHeight;
        else 
            node->height = 1 + rightHeight;

        node = node->parent;    // move to the parent node

        // update height of ancestor nodes
        while (node != NULL)
        {
            leftHeight = heightOf(node->left);
            rightHeight = heightOf(node->right);

            if (leftHeight > rightHeight) 
                node->height = 1 + leftHeight;
            else 
                node->height = 1 + rightHeight;
                
            node = node->parent;    // move to the parent node
        }
    }
}

/*
** function: rightRotate
** requirements:
    a non-null AVL pointer and a non-null node pointer
** results:
    rotates the tree (or subtree) rooted at `node` to the right
*/
void rightRotate(AVL* A, AVL_NODE * node)
{
	AVL_NODE *parent = node->parent;    // parent of critical node
	AVL_NODE *leftChild = node->left;   // pivot node // left child of critical node
	AVL_NODE *grandChild = leftChild->right;    // right subtree of pivot node
	
	if (parent == NULL)
		A->root = leftChild;    
	else 
	{
		// identify if node is left child or right child of parent
		if (parent->key < node->key)
			parent->right = leftChild;
		else if (parent->key > node->key)
			parent->left = leftChild;
	}

	leftChild->parent = parent; // parent of critical node becomes the parent of pivot
	leftChild->right = node;    // critical node becomes the right child of pivot
	node->parent = leftChild;	// parent becomes the left child
	node->left = grandChild;	// left child holds the right subtree 

    updateHeight(node);
}

/*
** function: leftRotate
** requirements:
    a non-null AVL pointer and a non-null node pointer
** results:
    rotates the tree (or subtree) rooted at `node` to the left
*/
void leftRotate(AVL* A, AVL_NODE * node)
{
	AVL_NODE *parent = node->parent;
	AVL_NODE *rightChild = node->right;			// pivot node // right child of critical node
	AVL_NODE *grandChild = rightChild->left;    // left subtree of pivot node
	
	if (parent == NULL)
		A->root = rightChild;
	else 
	{
		// identify if node is left child or right child of parent
		if (parent->key < node->key)
			parent->right = rightChild;
		else if (parent->key > node->key)
			parent->left = rightChild;
	}

	// SAME AS RIGHT ROTATE
	rightChild->parent = parent;
	rightChild->left = node;
	node->parent = rightChild;
	node->right = grandChild;

    updateHeight(node);	// update height of nodes
}


/*
** function: AVLInsert
** requirements:
    a non-null AVL pointer and a non null node pointer
** results:
    inserts the given node, `node`, to the AVL tree described by `A`
*/
void AVLInsert(AVL* A, AVL_NODE* node)
{
	// call insert function
	insert(A, node);

	BST_NODE *critical = NULL;
	BST_NODE *pivot = NULL;

	do {// traverse from inserted node up to the root
		// check if there is imbalance
		if (abs((heightOf(node->left) - heightOf(node->right))) > 1)
		{
			critical = node;

			if (heightOf(node->left) > heightOf(node->right))
			{
				pivot = node->left;
				if (heightOf(pivot->left) > heightOf(pivot->right))
                {
					//LEFT-LEFT LEANING
					rightRotate(A, node);	// right rotate on critical or node
                }
				else if (heightOf(pivot->left) < heightOf(pivot->right))
				{
					//LEFT-RIGHT LEANING
					leftRotate(A, pivot);
					rightRotate(A, critical);
				}
			}
			else if (heightOf(node->left) < heightOf(node->right))
			{
				pivot = node->right;
				if (heightOf(pivot->left) < heightOf(pivot->right))
                {
					//RIGHT-RIGHT LEANING 
					leftRotate(A, node);	//left rotate on critical or node
                }
				else if (heightOf(pivot->left) > heightOf(pivot->right))
				{
					//LEFT-RIGHT LEANING
					rightRotate(A, pivot);
					leftRotate(A, critical);
				}
			}
            
			break;
		}

		else node = node->parent; // move to the parent node

	} while (node != NULL);
}




/**** FUNCTIONS ABOVE **************************************/

int main(){

	char command;
	int key, result;

	AVL *A = createAVL(100);
	AVL_NODE* node;
	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf("%d", &key);
				printf("Inserting key: %d\n", key);
				AVLInsert(A, createAVLNode(key));
				break;
			case 'p':
				printf("Tree (rotated +90 degrees): \n");
				showTree(A);
				printf("\n");
				break;
			case 'C':
				printf("Removing all contents.\n");
				clear(A);
				break;
			case 'Q':
				clear(A);
				free(A);
				return 0;
            default:
                printf("Unknown command %c\n", command);
       }
    }
}
