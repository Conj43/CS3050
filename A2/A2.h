#include <stdio.h>
#include <stdlib.h>


typedef struct treeInfo {
    int data;
    struct treeInfo * right;
    struct treeInfo * left;
}treeInfo;

typedef struct BST {
    treeInfo * head;
    int size;
}BST;