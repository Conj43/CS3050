#include"A3.h"


Bucket * initBucketArray(int n)
{   
    Bucket * p = malloc((sizeof(Bucket))*n);
    for(int i = 0; i<n; i++)
    {
        p[i].min = 0;
        p[i].max = 0;
    }
    return p;
}

void freeBucketArray(Bucket * p)
{
    free(p);
}

float * findMinMax(float array[], float * min, float * max, int n)
{
    *min = array[0];
    *max = array[0];
    int minIndex = 0;
    int maxIndex = 0;
    if(n > 2)
    {
    int j = 0;
    for(int i = 0; i<n; i++)
    {
        if(array[i] < *min)
        {
            *min = array[i];
            minIndex = i;
        }
        else if(array[i] > *max)
        {
            *max = array[i];
            maxIndex = i;
        }
    }
    float tempMin = array[0];
    array[0] = array[minIndex];
    array[minIndex] = tempMin;

    float tempMax = array[n-1];
    array[n-1] = array[maxIndex];
    array[maxIndex] = tempMax;
    return array;
    }
    else
    {
        if(n==2)
        {
            if(array[0] > array[1])
            {
                *min = array[1];
                *max = array[0];
                float tempMin = array[0];
                array[0] = array[1];
                array[1] = tempMin;
            
                return array;
            }
            else if(array[0] < array[1])
            {
                *min = array[0];
                *max = array[1];
                return array;
            }
            else if(array[0] == array[1])
            {
                *min = array[0];
                *max = array[1];
                return array;
            }
        
        }
        else if(n==1)
        {
            *min = array[0];
            *max = array[0];
            return array;
        }
        else if(n==0)
        {
        return NULL;
        }
    }
    return NULL;
}
int interpolationSearch(float array[], int n, float k)
{
    //printf("array[0] = %f, n = %d, k = %f, array[n-1] = %f\n", array[0], n, k, array[n-1]);
    double ratio = ((k)-array[0])/((array[n-1])-(array[0]));
    //printf("%f\n", ratio);
    int index = ratio*(n-1);
    //printf("%d\n", index);
    return index;
}

void findWidestPair(Bucket p, Bucket * array, int currentIndex, float * minPair, float * maxPair, float * difference, int n, float max)
{
    int j = currentIndex;
    if(p.min != 0)
    {
        if(currentIndex==0)
        {
            if((array[currentIndex+1].min - p.max) > *difference)
            {
                puts("a");
                *minPair = p.max;
                *maxPair = array[currentIndex+1].min;
                *difference = (*maxPair)-(*minPair);
            }
        }
        else if(currentIndex > 0 && currentIndex < (n-1))
        {
            
            if(array[currentIndex+1].min != 0)
            {
                if((array[currentIndex+1].min - p.max) > *difference)
            {
                puts("b");
                *minPair = p.max;
                *maxPair = array[currentIndex+1].min;
                *difference = (*maxPair)-(*minPair);
            }
            }
            if(array[currentIndex-1].min != 0)
            {
                if((p.min - array[currentIndex-1].max > *difference))
            {
                puts("c");
                *minPair = array[currentIndex-1].max;
                *maxPair = p.min;
                *difference = (*maxPair)-(*minPair);
            }
            }
            if(array[currentIndex+1].min == 0)
            {
                while(array[j].min == 0 && j <= (n-1))
                {
                    j++;
                }
            if(j == (n-1))
            {
                if(max - p.max > *difference)
                {
                    puts("d");
                    *minPair = p.max;
                    *maxPair = max;
                    *difference = *maxPair - *minPair;
                }
            }
                if((array[j].min - p.max) > *difference)
            {
                puts("e");
                *minPair = p.max;
                *maxPair = array[j].min;
                *difference = (*maxPair)-(*minPair);
            }
            }
            if(currentIndex == (n-1))
            {
                if(max - p.max > *difference)
                {
                    puts("f");
                    *minPair = p.max;
                    *maxPair = max;
                    *difference = *maxPair - *minPair;
                }
            }
        }
    }
    printf("difference = %f\nminPair = %f\nmaxPair = %f\n\n", *difference, *minPair, *maxPair);
}

float findClusterExtreme(float array[], int n)
{
    float min = 0, max = 0;
    int index = 0;
    array = findMinMax(array, &min, &max, n);
    Bucket * newArr = NULL;
    newArr = initBucketArray(n-1);
    float minPair = 0, maxPair = 0, difference = 0;
    for(int i = 1; i<(n-1); i++)
    {
        index = interpolationSearch(array, n, array[i]);
        //printf("index[%d] = %d\n", i, index);
        if(index >= 0 && index <= n-1)
        {
            if(newArr[index].min == 0 && newArr[index].max == 0)
            {
                newArr[index].min = array[i];
                newArr[index].max = array[i];
            }
            else if(newArr[index].min > array[i])
            {
                newArr[index].min = array[i];
            }
            else if(newArr[index].max < array[i])
            {
                newArr[index].max = array[i];
            }
        }
    }
    printf("\n");
    for(int i = 0; i<(n-1); i++)
    {
        printf("newArr[%d].min = %f\n", i, newArr[i].min);
        printf("newArr[%d].max = %f\n", i, newArr[i].max);
    }
    printf("\n");
    minPair = min;
    maxPair = newArr[0].min;
    difference = maxPair - minPair;
    int j = 0;
    printf("difference = %f\nminPair = %f\nmaxPair = %f\n\n", difference, minPair, maxPair);
    for(int i = 0; i<(n-1); i++)
    {
        findWidestPair(newArr[i], newArr, i, &minPair, &maxPair, &difference, n-1, max);
    }
    printf("difference = %f\nminPair = %f\nmaxPair = %f\n\n", difference, minPair, maxPair);
    free(newArr);
    return minPair;
    
}

