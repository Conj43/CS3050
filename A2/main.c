#include "A2.h"
//connor joyce cpjtdx

int main(void)
{
    //RBST tree = initRBST();
    srand48(time(NULL));
    srand(time(NULL));
    int min = 0;
    int max = INT_MAX;
    int k;
    int size = 50;
    int loops = 1000;
    int * arr = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++)
    {
        k = rand() % (max - min + 1) + min;
        arr[i] = k;
    } 
    //int nodes = testInsertRBST(size, arr);
    //printf("nodes visited: %d\n", nodes);


    long int avg_nodes = scalingTests(loops, size, arr);
    printf("avg nodes = %ld\n", avg_nodes);

    int freed = testFreeRBST(size, arr);
    printf("nodes freed should be size: %d\n", freed);
    /*
    for(int i = 0; i<10; i++)
    {
        insertRBST(tree, arr[i]);
        preOrderPrintRBST(tree);
        printf("\n\n");
    }
    printf("root = %d\n", tree.k->root->data);
    if (tree.k->root->right)
    {
    printf("right = %d\n", tree.k->root->right->data);
    }
    if (tree.k->root->left)
    {
    printf("left = %d\n", tree.k->root->left->data);
    }
    */

    /*int arr[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int index = 0;
    findIndex(arr, 22, &index, 9, 0);
    printf("index : %d\n", index);
    */
    //int nodes_freed = testFreeRBST(tree);
    //printf("%d nodes\n", nodes_freed);
    free(arr);
} 