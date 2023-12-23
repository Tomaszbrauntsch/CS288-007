#include <stdio.h>
#include <stdlib.h>

/* Tomasz Brauntsch
   Professor Ding
   CS 288-007
   October 26, 2023
*/

int main(int argc, char ** argv){
    int buf;
    int i = 0;

    /* input from stdin */
    fscanf(stdin,"%d", &buf);
    int totalIntegers = buf; /* get the number of total integers */
    int myarr[totalIntegers];
    while(fscanf(stdin, "%d", &buf) != EOF){
        myarr[i] = buf;
        i++;
    }

    int bucket_index, rounds;
    int lenArr = (sizeof(myarr) / 4);
    int buffer[lenArr];
    int counter[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int offset[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int * p = myarr;
    int * q = buffer;
    int * temp = NULL;
    /* int i; */
    for (rounds = 0; rounds < 8; rounds++){
        for(i = 0; i < lenArr; i++){
            bucket_index = (p[i] >> rounds * 4) & 0xF;
            counter[bucket_index]++;
        }
        offset[0] = 0;
        for (i = 1; i < 16; i++){
            offset[i] = offset[i-1] + counter[i-1];
        }
        for (i = 0; i < lenArr; i++){
            bucket_index = (p[i] >> rounds * 4) & 0xF;
            q[offset[bucket_index]] = p[i];
            offset[bucket_index]++;
        }
        /* swap */
        temp = p;
        p = q;
        q = temp;
        for (i = 0; i < 16; i++){
            counter[i] = 0;
        }
    }
    int fixedArray[lenArr];
    int currentPosition = 0;
    for(i = 0; i < lenArr; i++){ /* Gets the negatives and adds it to the new array */
        if(p[i] < 0){
            fixedArray[currentPosition] = p[i];
            currentPosition++;
        }
    }
    for(i = 0; i < lenArr; i++){ /* Gets the positives and adds it to the new array */
        if(p[i] > 0){
            fixedArray[currentPosition] = p[i];
            currentPosition++;
        }
    }

    /* Prints the final amount */
    for (i = 0; i < lenArr; i++){
        printf("%d\n", fixedArray[i]);
    }
}