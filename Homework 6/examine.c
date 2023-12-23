#include <stdio.h>
#include <ctype.h>
#include <string.h>
/*
Tomasz Brauntsch
Professor Ding
CS 288-007
November 17, 2023
*/
int main(int argc, char * argv[]){
    int i,j;
    unsigned int * lastbitAddr;
    int lastbit, offset; /* offset is used when doing the printing */
    char * startingaddress, * currentAddr;
    int totalChars = 0;
    for (i = 0; i < argc; i++){
        totalChars += strlen(argv[i]); /* Get the total chars; used to print out the string data a correct amount of times*/
    }
    totalChars += argc; /* accounts for the null bytes */
    printf("argv\t| %p | %p\n", &argv[0], &argv);
    printf("\n");
    for(i=0;i<argc;i++){
        printf("argv[%d]\t| %p | %p\n", i, argv[i], &argv[i]);
    }
    printf("\n");
    lastbitAddr = (unsigned int *) &argv[0];
    lastbit = *(lastbitAddr) & 0xF;
    if(15-lastbit > lastbit)
    {
        /* when need to be 0*/
        offset=lastbit;
        startingaddress = argv[0] - lastbit;
        
    }
    else{
        /* when needs to be 8*/
        offset=lastbit-8;
        startingaddress = argv[0] - (lastbit-8);
        
    }
    i = 0;
    while(i-offset <= totalChars){
        currentAddr = startingaddress + (8*(i/8));
        printf("| ");
        for(j=8;j>0;j--){
            if(isprint(*(currentAddr+j)))
                printf("%02hhx(%c) ", (*(currentAddr+j)),(*(currentAddr+j)));
            else
                printf("%02hhx(\\%d) ", (*(currentAddr+j)),(*(currentAddr+j)));
            i++;
        }
        printf("\t| %p\t\n", currentAddr);
    }
    return 0;
}