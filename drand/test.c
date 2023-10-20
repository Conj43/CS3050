#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    // Seed the random number generator with the current time
    srand48(time(NULL));

    // Generate and print 5 random numbers
    for (int i = 0; i < 5; i++) {
        double randomValue = drand48();
        printf("Random number %d: %f\n", i + 1, randomValue);
    }

    return 0;
}

