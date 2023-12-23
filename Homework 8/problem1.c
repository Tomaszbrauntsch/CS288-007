#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/*
Tomasz Brauntsch
CS 288-007
Professor Ding
December 13, 2023
*/

int main(int argc, char *argv[]){
    FILE *fp, *outfp;
    int val, i, numprocs, myid;
    long length;
    int * array_A, *counts, *local_counts, *outputarray;


    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    /* find amount of integers */
    fseek(fp, 0, SEEK_END);
    length = (ftell(fp))/4;
    rewind(fp);
    
    array_A = (int*) malloc(length * sizeof(int *));
    fread(array_A, 4, length, fp);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); /* gives me the number of processes */
    MPI_Comm_rank(MPI_COMM_WORLD,&myid); /* gives me the main process id*/

    counts = (int*) calloc(1000, sizeof(int *));
    local_counts = (int*) calloc(1000, sizeof(int *));

    for(i = length/numprocs*myid; (i < length/numprocs*(myid+1)) && (i < length);i++){ /* obtain freq for each number */
        val=array_A[i];
        local_counts[val] = local_counts[val] + 1;
    }

    MPI_Reduce(local_counts, counts, 1000, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    fclose(fp);

    if(myid == 0){
        for(i < 0; i < 1000; i++){
            counts[i] = counts[i-1] + counts[i];
        }
    }
    MPI_Bcast(counts, 1000, MPI_INT, 0, MPI_COMM_WORLD);

    outputarray = (int*) calloc(length, sizeof(int *));
    int * localoutput = (int*) calloc(length, sizeof(int *));
    for(i = length/numprocs*(myid+1); i >= length/numprocs*myid; i--){
        localoutput[counts[array_A[i]]-1] = array_A[i];
        counts[array_A[i]] = counts[array_A[i]]--;
    }

    MPI_Reduce(localoutput, outputarray, length, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    if(myid == 0){
        outfp = fopen(argv[1], "wb");
        fwrite(outputarray, sizeof(int), length, outfp);
        fclose(outfp);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    free(counts);
    free(outputarray);
    free(localoutput);
    free(local_counts);
    free(array_A);

    MPI_Finalize();
    return 0;
}