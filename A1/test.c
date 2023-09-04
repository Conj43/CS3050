#include "A1.h"

int main(void)
{
    srand48(time(NULL)); // this needs to be initiialized somewhere, we can't do it in the function because we are looping through it and if we did it would cause drand to never change
    int test = testRandomSample(); // sets an int equal to our test function
    if (test == 0) // this would indicate a success, and our obtainRandomSample works correctly
    {
        printf("Congratulations! Your function correctly samples random integers!\n");
    }
    if (test == -1) // this would indicate failure
    {
        printf("Your function did not work!\n");
    }
}