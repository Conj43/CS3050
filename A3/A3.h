#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
#include<time.h>

typedef struct buck{
    float min;
    float max;
}Bucket;

float findClusterExtreme(float array[], int n);   //n is size of array and returns smaller value of the widest-seperated pair in the array
int interpolationSearch(float array[], int n, float k);
Bucket * initBucketArray(int n);
float * findMinMax(float array[], float * min, float * max, int n);
void freeBucketArray(Bucket * p);