#include "A2.h"




RBST initRBST() //initializes an RBST struct, which is a wrapper to a WRAP struct
{
    RBST tree;
    tree.k = malloc(sizeof(WRAP));
    if(!tree.k) //check if malloc worked
    {
        return tree;
    }
    
    tree.k->root = malloc(sizeof(treeInfo));
    if(!tree.k->root) //check if malloc worked
    {
        free(tree.k); //free memory we malloc'd and set equal to NULL
        tree.k = NULL;
        tree.k->root = NULL;
        return tree;
    }
    tree.k->root->right = NULL; //initialize each pointer in the root node
    tree.k->root->left = NULL;
    tree.k->size = 0; //set size and data = 0
    tree.k->root->data = 0;
    return tree; //return the initialized RBST struct
}

treeInfo * createNode(int data) //initializes a node, which is treeInfo struct
{
    treeInfo * new = malloc(sizeof(treeInfo));
    if(new) // check if malloc worked
    {
    new->left = NULL;
    new->right = NULL;
    new->data = data; //pass in data and set it to the node
    return new;
    }
    else return NULL; // return NULL if malloc didnt work
}

/*recursive func that takes a double pointer to the root node, the data being inserted, an error code variable
and an integer to keep track of how many nodes we visit
uses pass by reference for the root in order to make sure it changes the root pointer correctly
uses pass by reference for the error code variable and node_count
*/
void recursiveInsert(treeInfo ** root, int data, int * ec, int * node_count)
{

    if(*root == NULL)// we know we can insert here
    {
        treeInfo * new = createNode(data);
        if (new == NULL) // check if malloc worked
        {
            *ec = -1; //set ec to -1 if it didn't work
        }
        *root = new; // set new branch to current root
        (*node_count)++; //increase node_count by one, because we visited a new node
        return; //exit out of function
    }
    else if((*root)->data > data) // if data < current data we pass it to the left
    {
        (*node_count)++;  //increase node_count by one, because we visited a new node
        recursiveInsert(&((*root)->left), data, ec, node_count); // recursive call 
    }
    else if ((*root)->data < data) // if data > current data we pass it to the right
    {
        (*node_count)++;  //increase node_count by one, because we visited a new node
        recursiveInsert(&((*root)->right), data, ec, node_count); // recursive call
    }

}

/*this function uses an inorder traversal algorithm to flatten the RBST into a sorted array
it takes a treeInfo pointer, which is the root node
it takes the array that we will be filling, and uses pass by reference to keep track of the index we are at*/
void inorderTraversal(treeInfo * root, int* result, int* index) 
{
    if (root == NULL) return; //we reached end of RBST
    inorderTraversal(root->left, result, index); //goes to the left first to find smallest element
    result[(*index)++] = root->data; //fills array
    inorderTraversal(root->right, result, index); //goes to the right last so we go in ascending order
}
/* this function is a helper function to inOrderTraversal, it just makes it cleaner to be able to pass the information to
this function then use a recursive algorith in inOrderTraversal
it just takes the array you want to fill, and the root node and since we are using pointer, it will change the 
array in the function*/
void flattenRBST(treeInfo* root, int * array)
{
    int index = 0; //set index to 0 to start
    inorderTraversal(root, array, &index); //use pass by reference to keep track of index
}

/* this function is used to randomly build our RBST
it takes the flattened array, and a min index and a max index
it returns a node pointer which will be the root node of that subtree*/
treeInfo * rebuildRBST(int * array, int max, int min)
{
    if (min>max) //if min index > max index we know we are done and can stop
    {
        return NULL;
    }
    int k = rand() % (max - min + 1) + min; //generates random index between min and max
    if(k >= min && k<= max) //make sure k is in the bounds
    {
    treeInfo * new = createNode(array[k]); //create new node using value from random index
    new->left = rebuildRBST(array, k-1, min); //use values betwwen index-1 and min for the left subtree of new node
    new->right = rebuildRBST(array, max, k+1); //use values between index+1 and max for right subtree (we know we can do this because the array is in sorted order)
    return new; //return the new node
    }
    return NULL; //if k was not within the bounds, return NULL
}

/* this function finds where the new node needs to fit into the subtree
we use binary search to find where the new node goes, and we use pass by reference to change the index and be able to return it
we take the sorted array, the key is the new node data, the index to pass by reference, the max index of the array
the min index of the array, and use a variable to keep track of the current index*/
void recursiveFind(int * array, int key, int * index, int max, int min, int current_index)
{
    if(current_index >= min && current_index <= max) //make sure current index is within the bounds
    {
    if(array[current_index] < key && array[current_index+1] > key) //if new node is between array[index] and array[index+1] we know where the node goes
    {
        *index = current_index; //we set it equal to the index that has the closest value to the key that is less than it
        return; //exit the function
    }
    else if(key < array[current_index]) //if key is less than current value, look to the left
    {
        max = current_index; //change value of max to calculate current index
        recursiveFind(array, key, index, current_index, min, (min+max)/2); 
    }
    else if(key > array[current_index])// if key is greater than current value, look to the right
    {
        min = current_index+1; //change value of min to calculate current index
        recursiveFind(array, key, index, max, current_index+1, (min+max)/2);
    }
    else if(key == array[current_index]) //just a special case, i think we are assuming we dont have any repeat keys
    {
        *index = current_index;
        return;
    }
    }
}

/*this function is related to recursiveFind, and is mainly used for special cases
it takes the same exact parameters as the function before, and does the same things
but in order to have it recursive, we can't check for the special cases everytime, so i split it up
and it will check for the special cases here then transfer over if none of the special cases are occuring*/
void findIndex(int * array, int key, int * index, int max, int min, int current_index)
{
    
    if(max == 0) //this is when there is one element in the array
    {
        *index = 0; //we return the index as 0, because it is the only element in the array
        return; //exit function
    }
    if(array[max] < key) //if our new node is greater than any element in the array
    {
        *index = max; // we know we just need the max index, since it is bigger so we don't need to search
        return;
    }
    if(array[min] > key) //if new node is less than any element in the array
    {
        *index = -1; // we set it to -1 because we will increment it by one in our start rebuild function, so it ends up being 0
        return;
    }
    //this is same logic as function before, it just transfers over to other function to use recursion
    if(current_index >= min && current_index <= max)
    {
    if(array[current_index] < key && array[current_index+1] > key)
    {
        *index = current_index;
        return;
    }
    else if(key < array[current_index])
    {
        max = current_index;
        recursiveFind(array, key, index, current_index, min, (min+max)/2);
    }
    else if(key > array[current_index])
    {
        min = current_index+1;
        recursiveFind(array, key, index, max, current_index+1, (min+max)/2);
    }
    else if(key == array[current_index])
    {
        *index = current_index;
        return;
    }
    }
    
}

/* this function starts the rebuild of the RBST by finding the index, creating the root node, and 
starting to make the left and right subtrees
it takes the sorted array, a max index of the array, a min index of the array and the size of the array*/
treeInfo * startRebuild(int * array, int max, int min, int n, int size)
{
    int index = -1; //sets index to -1 and we change it in findIndex
    treeInfo * new = createNode(n); //creates new root node
    
    findIndex(array, n, &index, size-1, 0, (min+max)/2); //finds index of root node in sorted array
    
    if(min == 0 && max == 0) //special case, if there is only one element in the array, min and max == 0 so we can just 
    {                           //check if it should go to the right or left subtree
        if(array[0] > n) //goes to right
        {
            new->right = rebuildRBST(array, max, min);
            new->left = NULL;
        }
        else if (array[0] < n)//goes to left
        {
            new->left = rebuildRBST(array, max, min);
            new->right = NULL;
        }
    }
    else //if there is more than one element in the array
    {
    
    new->left = rebuildRBST(array, index, min); //recursively build left and right subtrees
    new->right = rebuildRBST(array, max, index+1); //recursively build left and right subtrees
    }
    return new; //returns root node with newly built left and right subtrees attatched
}

/* this function inserts a new node into a RBST
using probability 1/tree_size+1 we rebuild the entire tree with the new node at the root
if we don't rebuild, we can just insert the new node normally at the end of the tree
this allows each node to have an equally likely chance at being the root node
the only parameters we have are an RBST tree and the data of the new node
this function returns the total number of nodes visited during this insertion, in order to help us determine complexity*/
int insertRBST(RBST tree, int n)
{
    int ec = 0; // we use this as an error code
    treeInfo * temp = tree.k->root; // use this to help us free the old tree
    int nodes_visit = 0; // use this to determine number of nodes visited
    if(tree.k->size == 0) //if tree is empty
    {
        tree.k->root->data = n;
        tree.k->size++; // we already set pointers to NULL in init function, so we just increase size and set data 
        return 1; // we can only return 0 on error
    }
    if(tree.k->size > 0) //if tree is not empty
    {
        double random = drand48(); // set random equal to random value between 0.0 and 1.0
        if (random < (1.0/(tree.k->size+1))) // using probability to determine if we rebuild
        {
            int size = tree.k->size; // transfer size over to int variable for convenience
            int* array = NULL;
            array = malloc(sizeof(int) * size); //initialize array and malloc for size of size*sizeof(int)
            if(!array)
            {
                return 0; //if malloc did not work
            }
            if (array) // if malloc worked we go through
            {
                flattenRBST(tree.k->root, array); //flattens RBST into a sorted array
                treeInfo * temp = tree.k->root; //set temp = root so we can free
                tree.k->root = startRebuild(array, size-1, 0, n, size); // set root equal to the new tree using a rebuild
                freeTree(temp, &nodes_visit); //free temp to free the old tree
            }
            free(array); //free array we used
            nodes_visit = tree.k->size; // when we rebuild, we visit each node so we will end up returning the size of the tree
        }
        else 
        {
            temp = tree.k->root; // make sure temp is properly set
            recursiveInsert(&(temp), n, &ec, &(nodes_visit)); //use normal insertion and pass by reference to count nodes visited
            if(ec == -1)
            {
                return 0; //means malloc didn't work for new node
            }
        }
    }
    tree.k->size++; // make sure we increase size of tree
    return nodes_visit; //return nodes visited
}

/*this function recursively frees every node starting by passing in the root
we use pass by reference to count how many nodes we free*/
void freeTree(treeInfo * q, int * n)
{
    if (q == NULL) return;
    freeTree(q->left, n);
    freeTree(q->right, n);
    free(q);
    (*n)++; //increase nodes freed by one
}

/*this is the function we use to free, it calls the recursive free function
all we take is a RBST struct and we return the number of nodes freed*/
int freeRBST(RBST tree)
{
    int n = 0; //initialzie number of nodes freed
    freeTree(tree.k->root, &n);
    free(tree.k); //make sure to free the memory we malloc'd for WRAP
    return n; //returns number of nodes we freed in this call
}

//used this function to check how well my trees were working
//this prints a tree in sorted order from least to greatest
void recursivePrint(treeInfo * p) //just takes the root node of a RBST
{
    if (p==NULL) return; //if NULL then exit function
    recursivePrint(p->left);
    printf("key: %d\n", p->data);
    recursivePrint(p->right);
}

void printRBST(RBST tree) //just calls recursive function to print in order
{
    recursivePrint(tree.k->root);
}

/* this function is used to help determine complexity of out insertRBST function
it takes an int array and the size of it and inserts it into an RBST
it counts how many nodes are visited throughout this process, and returns it*/
int testInsertRBST(int n, int * arr)
{
    int nodes = 0;
    int temp = 0;
    RBST tree = initRBST(); //make new RBST
    for(int i = 0; i<n; i++)
    {
        temp = insertRBST(tree, arr[i]); //loop through and insert each node
        nodes = temp+nodes; //keep track of how many nodes are visited
    }
    freeRBST(tree); //frees the tree and it would return how many nodes are in our RBST at the end(the size)
    return nodes; //return how many nodes we visited during insertion
}

/* this function verifys that freeRBST is done in O(n) time
it does the same exact thing as testInsertRBST, but it returns the 
number of nodes freed instead of number visited
it should always be the same number as the size of the RBST*/
int testFreeRBST(int n, int * arr)
{
    int nodes = 0;
    int temp = 0;
    int size = 0;
    RBST tree = initRBST(); //make new RBST
    for(int i = 0; i<n; i++)
    {
        temp = insertRBST(tree, arr[i]); //loop through and insert each node
        nodes = temp+nodes; //keep track of how many nodes are visited
    }
    size = freeRBST(tree); //frees the tree and returns how many nodes are in our RBST at the end(the size)
    return size; //return how many nodes we freed, should be the same as the size b/c complexity is O(n)
}


/*this function returns the average of how many nodes are visited for the given amount of loops
it takes an integer loops, which is how many times the testInsertRBST function will run, an
integer array and the size of the array, using this function we can do some math to figure out our complexity*/
int scalingTests(int loops, int size, int * arr)
{
    int * count_array = NULL; //initialize array
    count_array = malloc(sizeof(int) * loops); //allocate memory for array
    int nodes;
    for(int i = 0; i<loops; i++)
    {
        nodes = testInsertRBST(size, arr); //loop through loops times and set a value from the array equal to the amount of 
        count_array[i] = nodes;  //nodes that were visited each time
    }
    int sum = 0;
    int avg = 0;
    for(int i = 0; i<loops; i++)
    {
        sum = sum+count_array[i]; //loop through the array and get the total sum
    }
    avg = sum/loops; //divide by loops to find average nodes visited
    free(count_array); //free array
    return avg; //return average number of nodes visited
}