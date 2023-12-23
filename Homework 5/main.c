#include <stdio.h>
#include <stdlib.h>

/* Tomasz Brauntsch
   Professor Ding
   CS 288-007
   November 8, 2023
*/


int main() {
    int totalIntegers;
    int i = 0;
    float currentNum;

    /* input from stdin */
    fscanf(stdin, "%d", &totalIntegers);
    float *myarr = (float *) malloc(totalIntegers * sizeof(float *));
    while (fscanf(stdin, "%f", &currentNum) == 1) {
        myarr[i] = currentNum;
        i++;
    }
    int bucket_index, rounds;
    float *buffer = (float *) malloc(totalIntegers * sizeof(float *));
    int counter[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    float* curr_locations[16];
    float *p = myarr;
    float *q = buffer;
    float *temp;
    unsigned int * bi_p;

    for (rounds = 0; rounds < 8; rounds++) {
        for (i = 0; i < totalIntegers; i++) {
            bi_p = (unsigned int *) &p[i];
            bucket_index = (*bi_p >> rounds * 4) & 0xF;
            counter[bucket_index]++;
        }
        curr_locations[0] = q;
        for (i = 1; i < 16; i++) {
            curr_locations[i] = (curr_locations[i - 1] + counter[i - 1]);
        }
        for (i = 0; i < totalIntegers; i++) {
            bi_p = (unsigned int *) &p[i];
            bucket_index = (*bi_p >> rounds * 4) & 0xF;
            *curr_locations[bucket_index] = p[i];
            curr_locations[bucket_index]++;
        }
        /* swap */
        temp = p;
        p = q;
        q = temp;
        for (i = 0; i < 16; i++) {
            counter[i] = 0;
        }
    }
    int currPos = 0;
    for (i = totalIntegers; i > 0; i--){
        if (p[i] < 0.0){
            buffer[currPos] = p[i];
            currPos++;
        }
    }
    for (i = 0; i < totalIntegers; i++) {
        if (p[i] > 0.0) {
            buffer[currPos] = p[i];
            currPos++;
        }
    }
    for (i = 0; i < totalIntegers; i++){
        printf("%f\n", buffer[i]);
    }
    free(myarr);
    free(buffer);
    p = NULL;
    q = NULL;

}