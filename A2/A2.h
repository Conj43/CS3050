#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct treeInfo {
    int data;
    struct treeInfo * right;
    struct treeInfo * left;
}treeInfo;

typedef struct BST {
    treeInfo * root;
    int size;
}WRAP;

typedef struct wrapper { 
    WRAP * k;
}RBST;

RBST initRBST();
int insertRBST(RBST tree, int n);
void freeTree(treeInfo * q, int * n);
int freeRBST(RBST tree);
void recursiveInsert(treeInfo ** root, int data, int * ec, int * node_count);
void inorderTraversal(treeInfo * root, int* result, int* index);
void flattenRBST(treeInfo* root, int* array);
treeInfo * createNode(int data);
treeInfo * rebuildRBST(int * array, int max, int min);
void printRBST(RBST tree);
void recursivePrint(treeInfo * p);
void findIndex(int * array, int key, int * index, int max, int min, int current_index);
treeInfo * startRebuild(int * array, int max, int min, int n, int size);
void recursiveFind(int * array, int key, int * index, int max, int min, int current_index);
int testInsertRBST(int n, int * arr);
int testFreeRBST(int n, int * arr);
int scalingTests(int loops, int size, int * arr);
