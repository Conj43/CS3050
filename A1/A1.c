#include "A1.h"

int obtainRandomSample(int *sequence) // takes an integer array and returns a random integer in the array with no knowledge of size of array
{                                       // each integer in the list has an equal chance of being selected
    int num  = sequence[0]; // initialize variable we will be storing the random integer in to the first element in the array
    int count = 1; // start at one because we already initialized num to the first element
    while(sequence[count] != INT_MAX) // loop through until end of array 
    {
        count++; 
        double random_double = drand48(); // drand48 randomly generates a double betwen 0.0 and 1.0; must be initialized using srand48(time(NULL)) outside of the function
        if (random_double < 1.0 / count) //logic in order to randomly select an integer without knowing the length of the sequence
        {
            num = sequence[count - 1]; // need to count -1 in order to correctly assign the selected integer
        }
    }
    return num; // retruns randomly selected integer
}

int testRandomSample() //this function has no parameters, it just tests obtainRandomSample
{                     //if each integer in the sequence occurs within .3% of 5%, then it returns 0, otherwise it returns -1
    int count[20];
    int sequence[21] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,INT_MAX}; //we use a sequence of 20 integers, just 1-20 in chronological order
    int array[100000];

    for(int i = 0; i<100000; i++)
    {
        array[i] = obtainRandomSample(sequence); //this runs through 100,000 times and uses the obtainRandomSample to get a random integer from the sequence
    }

    for(int i = 0; i<20;i++)
    {
        count[i] = 0; // here we are going to use the count array to store how many times each integer occured, and we are just initializing each element to 0
    }

    int temp;
    for (int i = 0; i < 100000; i++) // this loops through the entire array, and for each occurence of an integer it adds one to the count array of the corresponding integer
    {
        temp = array[i];
        count[temp-1]++;
    }
    double count_d[20]; // this will be used to make the computation a little easier by converting it to percents

    for(int i = 0; i<20; i++)
    {
        count_d[i] = 0; //initalize array to 0's
    }

    for(int i = 0; i<20; i++)
    {
        count_d[i] = (double)count[i]; // transferring the counts over to our double array
    }

    for(int i = 0; i<20; i++)
    {
        count_d[i] = (count_d[i]/100000)*100; // this converts them each to a percent 
    }

    for(int i = 0; i<20; i++)
    {
        if(count_d[i] < 4.7 || count_d[i] > 5.3)  // if any number occured too much or too little, this will detect it with an error of about .3%
        {
            return -1; // if a percent was too high or low, we will return -1 indicating our obtainRandomSample does not work correctly
        }
    }

    return 0; // if everything goes through, we return 0 and this would be a success
}