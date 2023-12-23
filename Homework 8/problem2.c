#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

/*
Tomasz Brauntsch
Professor Ding
CS 288-007
December 13, 2023
*/

int nthreads, totalterms;
long double sum = 0.0;
sem_t sum_sem;

void *term_calculation(void *tid){
        int * currid = (int*) tid;
        long double x, i;
        long double partial_sum = 0.0;

        long chunk = totalterms / nthreads;
        long start = (*currid) * chunk;
        long end = start + chunk;

        if ((*currid) == nthreads - 1)
            end = totalterms;
        
        for (i = start; i < end; i++){
            x = ((double)i - 0.5) / totalterms;
            partial_sum += (4.0 / (1.0 + x * x));
        }
        sem_wait(&sum_sem);
        sum += partial_sum;
        sem_post(&sum_sem);
}

int main(int argc, char *argv[]){
    unsigned long n;
    long double PI = 3.14159265358979323846264338327950288419716939937510;
    long double pi;
    int i;
    pthread_t * thread_array;
    long *threads_ids;

    if (argc != 3){
        fprintf(stderr, "usage: %s <n> <t>\n", argv[0]);
        fprintf(stderr, "where <n> is the number of threads and <t> is the number of terms\n");
        return 1;
    }

    /* Semaphore setup */    
    sem_init(&sum_sem, 0,1);

    nthreads = strtol(argv[1], NULL, 10);
    totalterms = strtol(argv[2], NULL, 10);

    /* Initialize the threads */
    thread_array = malloc(nthreads * sizeof(pthread_t));
    threads_ids = malloc(nthreads * sizeof(long));
    for (i = 0; i < nthreads; i++){
        threads_ids[i] = i;
        pthread_create(&thread_array[i], NULL, term_calculation, &threads_ids[i]);
    }

    for ( i = 0; i < nthreads; i++){
        pthread_join(thread_array[i], NULL);
    }

    pi = sum/totalterms;
    printf("pi is approximately %.22Lf, Error is %.22Lf\n", pi, fabsl(pi - PI));

    sem_destroy(&sum_sem);
    free(thread_array);
    free(threads_ids);
}