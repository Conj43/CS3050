#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
#include<time.h>
#include<float.h>

typedef struct buck{
    float min;
    float max;
}Bucket;

float findClusterExtreme(float array[], int n);   //n is size of array and returns smaller value of the widest-seperated pair in the array
int interpolationSearch(float array[], int n, float k);
Bucket * initBucketArray(int n);
float * findMinMax(float array[], float * min, float * max, int n);
void findWidestPair(Bucket p, Bucket * array, int currentIndex, float * minPair, float * maxPair, float * difference, int n, float max);
clock_t startTime();
double endTime(clock_t begin);
double scalingtTest(int size, int i);