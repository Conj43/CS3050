#include"A3.h"

int main(void)
{
    srand(time(NULL));
    int size = 10;
    float randomNum;
    //int maxP = INT_MAX;
    //int minP = 100000;
    //int maxK = 99999;
    //int minK = 1;
    int maxP = 20;
    int minP = 10;
    int maxK = 9;
    int minK = 2;
    float * arr = NULL;
    int k;
    int p;
    arr = malloc(sizeof(float)*size);
    float min = 0;
    float max = 0;
    for(int j = 0;j<size; j++)
    {
        k = rand() % (maxK - minK + 1) + minK;
        p = rand() % (maxP - minP + 1) + minP;
        randomNum = (float)p/k;
        arr[j] = randomNum;
    }
    /*for(int i = 0; i<size; i++)
    {
        printf("arr[%d] = %f\n",i, arr[i]);
    }
    */
    arr = findMinMax(arr, &min, &max, size);
    printf("min = %f\nmax = %f\n", min, max);
    for(int i = 0; i<size; i++)
    {
        printf("arr[%d] = %f\n",i, arr[i]);
    }
    float r = findClusterExtreme(arr, size);
    printf("r = %f\n", r);
    bubbleSort(arr, size);
    for(int i = 0; i<size; i++)
    {
        printf("arr[%d] = %f\n",i, arr[i]);
    }
    free(arr);


}