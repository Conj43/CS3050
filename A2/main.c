#include "A2.h"

/*my function takes nothing and returns a pointer to a BST, it mallocs a BST to initialzie the BST pointer
and also mallocs for the head of the tree
we then initalize left and right of the head to NULL and data and size to 0 and can the return the BST pointer back to the user*/
BST * initBST()
{
{
    BST * p = malloc(sizeof(BST));
    p->head = malloc(sizeof(treeInfo));
    if (!p) // check if malloc worked, if it didnt then this will return NULL
    {
        return p;
    }
    else if (p)
    {
        p->head->right = NULL;
        p->head->left = NULL;
        p->head->data = 0;
        p->size = 0;
    }
    return p; // returns BST pointer
} 
}