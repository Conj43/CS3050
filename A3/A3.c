#include"A3.h"
//WSP = widest seperated pair
/*this function allows us to measure the time of the findClusterExtreme function. it just starts our timer or counter, it returns a clock_t
which is just an unsigned long int, i found this function on stack overflow in order to measure how long my function takes
so that i can determine its complexity*/
clock_t startTime()
{
    clock_t begin = clock();
    return begin;
}

/*this function allows us to return the amount of time it takes for our function in seconds
like the previous function, i found this on stack overflow so that i could determine the complexity of findClusterExtreme
you pass in the origincal clock_t variable and find the difference between the curent and beginning values
then divide by clocks per second to convert it to time in seconds which we return as a double*/
double endTime(clock_t begin)
{
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    return time_spent; //return time spent in seconds
}

/*this function takes an integer, which is going to be the size of our bucket array
and it returns an initialized Bucket pointer which will be used as an array
it checks if malloc worked, and returns NULL if it did not work
if malloc worked, we return an initialized Bucket array that has every min and max value set equal to 0*/
Bucket * initBucketArray(int n)
{   
    Bucket * p = malloc((sizeof(Bucket))*n);
    if(p) //if malloc worked
    {
    for(int i = 0; i<n; i++)
    {
        p[i].min = 0; //set both to 0 so we know if empty
        p[i].max = 0;
    }
    return p;
    }
    else return NULL;
}

/*this function is passed an array of floats, the size of the array and two float pointers which will be changed using pass by reference
which indicate the min and max element of the array
it sequences through and finds the min and max element, it then puts the min element in 0th index of the array
and it puts the max element in the n-1 index of the array
it does this by just swapping its current index with the 0th or n-1 index in the array
it returns a float array that now has the min element in the 0th element and the max element in the n-1 element*/
float * findMinMax(float array[], float * min, float * max, int n)
{
    *min = array[0]; //initialize the the first element of the array
    *max = array[0];
    int minIndex = 0; //keep track of index so we can swap elements
    int maxIndex = 0;
    if(n > 2) //only want to go through if we have more than 2 elements, if we have 2 or less we can do a simple comparison to find min and max
    {
    int j = 0;
    for(int i = 0; i<n; i++)
    {
        if(array[i] < *min) // check if current value is less than current value stored in min
        {
            *min = array[i];
            minIndex = i;
        }
        else if(array[i] > *max) // check if current value is greater than current value in max
        {
            *max = array[i];
            maxIndex = i;
        }
    }
    float tempMin = array[0]; //swap min with the value at array[0]
    array[0] = array[minIndex];
    array[minIndex] = tempMin;
    if(maxIndex == 0) //special case if max value was at the 0th index
    {
        maxIndex = minIndex; //our max element is now where our min element was
    }
    float tempMax = array[n-1]; //swap max with value at array[n-1]
    array[n-1] = array[maxIndex];
    array[maxIndex] = tempMax;
    return array; //return new array with min and max in correct position
    }
    else
    {
        if(n==2) //if we have two elements, just check which element is bigger and swap accordingly
        {
            if(array[0] > array[1]) //if array[1] is smaller we swap and set min and mac accordingly
            {
                *min = array[1];
                *max = array[0];
                float tempMin = array[0];
                array[0] = array[1];
                array[1] = tempMin;
            
                return array;
            }
            else if(array[0] < array[1]) //if array[1] is bigger we just set min and max accordingly
            {
                *min = array[0];
                *max = array[1];
                return array;
            }
            else if(array[0] == array[1]) //if both elements are equal
            {
                *min = array[0];
                *max = array[1];
                return array;
            }
        
        }
        else if(n==1) //if we have an array of size one, our min and max are set to the only value in the array
        {
            *min = array[0];
            *max = array[0];
            return array;
        }
        else if(n==0)
        {
        return NULL; //if we have size 0 we return NULL
        }
    }
    return NULL;
}

/*this function uses the interpolationSearch formula to help us seperate the buckets and determine where each element goes
it takes a float array, the size of the array n, and the current value k, which is the value which we need to determine the index for
it uses a simple formula that we discussed in lecture and returns the index of the current value 
if the size passed in is less than 0, we return -1 because we want to create an error that notifies the user of 
the problem*/
int interpolationSearch(float array[], int n, float k)
{
    if(n > 0)
    {
    double ratio = ((k)-array[0])/((array[n-1])-(array[0]));
    int index = ratio*(n-1);
    return index;
    }
    else return -1;
}

/*This function is used to help find the widest pair
this speciic implementation is passed in a Bucket, the array of Buckets, the current index which is the index of the Bucket p
in the array It also is passed in the current minPair, maxPair and difference in order to keep track of the widest seperated pair
when we find a bigger seperated pair than the current one, we update the minPair, maxPair and difference
the function is also passed the size, n and the max value of the array
it doesnt return anything, it just updates the minpair, maxpair and difference variables using pass by reference WSP= widest seperated pair*/
void findWidestPair(Bucket p, Bucket * array, int currentIndex, float * minPair, float * maxPair, float * difference, int n, float max)
{
    int j = currentIndex+1; //used when the next bucket is 0
    if(p.min != 0) // if current bucket is not 0
    {
        if(currentIndex==0) //if this is the first element
        {
            if((array[currentIndex+1].min - p.max) > *difference) //check next bucket min and current max to see if it is WSP
            {
                *minPair = p.max;
                *maxPair = array[currentIndex+1].min;
                *difference = (*maxPair)-(*minPair);
            }
        }
        else if(currentIndex > 0 && currentIndex < (n-1)) //make surecurrent index is in the correct bounds
        {
            
            if(array[currentIndex+1].min != 0) //make sure next bucker is not empty
            {
                if((array[currentIndex+1].min - p.max) > *difference) //check if current max and next min is WSP
            {
                *minPair = p.max;
                *maxPair = array[currentIndex+1].min;
                *difference = (*maxPair)-(*minPair);
            }
            }
            if(array[currentIndex-1].min != 0) //make sure bucket behind is not empty
            {
                if((p.min - array[currentIndex-1].max > *difference)) //check if current min and previous max is WSP
            {
                *minPair = array[currentIndex-1].max;
                *maxPair = p.min;
                *difference = (*maxPair)-(*minPair);
            }
            }
            if(array[currentIndex+1].min == 0) //if next bucket is 0, we need to cycle through until we hit the next non-empty bucket
            {
                while(array[j].min == 0 && j < (n-1))
                {
                    j++;
                }
            if(j == (n-1) && array[j].min == 0) //if cycled through to last bucket at its 0, check if max value - current max is WSP
            {
                if(max - p.max > *difference) 
                {
                    *minPair = p.max;
                    *maxPair = max;
                    *difference = *maxPair - *minPair;
                }
            }
            if(currentIndex == (n-1)) //if we are looking at the last element
            {
                if(max - p.max > *difference)
                {
                    *minPair = p.max;
                    *maxPair = max;
                    *difference = *maxPair - *minPair;
                }
            }
            if((array[j].min - p.max) > *difference) // j is the index of the next non-empty bucket so we are checking if we had to cycle through
            {
                *minPair = p.max;
                *maxPair = array[j].min;
                *difference = (*maxPair)-(*minPair);
            }
            }
            
        }
    }
}

/*this is our main function that we use to find the WSP
it takes an array of floats, and the size of the array n
it goes through the array and finds the WSP, and returns the smaller number of the widest seperated pair
its complexity is O(n) because we need to sequence through the array to put it into buckets and once we have it in buckets,
we just need to sequence through and find the widest seperated pair, keeping track of each bucket*/
float findClusterExtreme(float array[], int n)
{
    float min = 0, max = 0;
    int index = 0;
    array = findMinMax(array, &min, &max, n); //helper function that finds min and max at puts them at 0th and n-1st element in array
    Bucket * newArr = NULL;
    newArr = initBucketArray(n-1); //initialize a Bucket array with size of n-1 because we arent going to put min or max in the bucket array and we need to guarantee at least one empty bucket
    if(newArr)
    {
    float minPair = 0, maxPair = 0, difference = 0;
    for(int i = 1; i<(n-1); i++) //only loop through the 1st to n-1 element because we are not using min or max value
    {
        index = interpolationSearch(array, n, array[i]); //find index for current element
        if(index >= 0 && index <= n-1)
        {
            if(newArr[index].min == 0 && newArr[index].max == 0) //if bucket is empty, set min and max equal to current element
            {
                newArr[index].min = array[i];
                newArr[index].max = array[i];
            }
            else if(newArr[index].min > array[i]) //look if we need to replace min
            {
                newArr[index].min = array[i];
            }
            else if(newArr[index].max < array[i]) //look if we need to replace max
            {
                newArr[index].max = array[i];
            }
        }
    }
    minPair = min;
    maxPair = newArr[0].min; 
    difference = maxPair - minPair; //initalize the variables as 0th element min - min of array so we account for that
    int j = 0;
    for(int i = 0; i<(n-1); i++)
    {
        findWidestPair(newArr[i], newArr, i, &minPair, &maxPair, &difference, n-1, max); //this function checks all cases for the current Bucket to see if the  WSP is at this element
    }
    free(newArr); //we malloc when we initalize the array so we have to free it
    return minPair; //return smaller of the WSP
    }
    else return FLT_MAX; //if malloc failed, return FLT_MAX
    
}

/*this is the function i used to find the complexity of the findClusterExtreme function
you choose how big you want the randomly generated array to be so you pass in size
then you choose how many times you want to test it, i, so that you can get the most accurate results
it returns the average time for the findClusterExtreme function for the size passed in for i tests */
double scalingtTest(int size, int i)
{
    srand(time(NULL)); //we generate our array using random numbers so we need to initialize rand
    float sum = 0;
    double timeOfFunc = 0;
    float randomNum;
    int maxP = INT_MAX; //P is what i use to generate the numerator for the random number
    int minP = 100000;
    int maxK = 99999; //K is for the denominator
    int minK = 2;
    float * arr = NULL;
    int k;
    int p;
    for(int n = 0; n < i; n++)
    {
    arr = malloc(sizeof(float)*size);
    if(arr) //check if malloc worked
    {
    float min = 0;
    float max = 0;
    for(int j = 0;j<size; j++)
    {
        k = rand() % (maxK - minK + 1) + minK;
        p = rand() % (maxP - minP + 1) + minP;
        randomNum = (float)p/k; //in order to get good float numbers, we generate two random numbers and divide them to create a float
        arr[j] = randomNum;
    }
    clock_t begin = startTime(); //start time
    float r = findClusterExtreme(arr, size);
    timeOfFunc = endTime(begin); //end time, so we just get the time of findClusterExtreme
    sum = sum + timeOfFunc; //keep track of total time
    free(arr);
    }
    else return -1; //if malloc doesnt work, return -1
    }
    return (sum/i); //return average time of findClusterExtreme in seconds
}
