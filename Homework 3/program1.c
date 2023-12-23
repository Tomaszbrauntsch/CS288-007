/*
Created By: Tomasz Brauntsch
Professor Ding
CS 288-007
October 17, 2023
*/

#include <stdio.h>
#include <stdlib.h>

main(){
    int row_size, col_size, i, colCount, rowCount, nonzeroCount, colindexCount, rowindexCount, elementPresent;
    unsigned int *all_elements, *nonzeroElements, *columnIndices, *rowStart;
    FILE * stream, * writefile;
    stream = fopen("matrix.bin", "rb");
    if (stream == NULL)
        perror("fopen");
    
    unsigned int sizes[2];
    fread(sizes, 4, 2, stream); /* used to parse out the row and column size*/
    row_size=sizes[0];
    col_size=sizes[1];
    all_elements = (unsigned int*)malloc((row_size*col_size) * sizeof(unsigned int*)); /* All elements in the bin file*/
    nonzeroElements = (unsigned int*)malloc((row_size*col_size) * sizeof(unsigned int*));
    columnIndices = (unsigned int*)malloc((row_size*col_size) * sizeof(unsigned int*));
    rowStart = (unsigned int*)malloc((row_size+1) * sizeof(unsigned int*));
   
    fread(all_elements, 4, row_size*col_size, stream); /* used to parse out the remaining bytes (the elements) */
    
    /*xxxCount is used for counting all the rows/columns/nonzero elements*/
    colCount=0;
    rowCount=0;
    nonzeroCount=0;

    /* xxxindexCount is used for total number of items in the columnIndices and rowStart mallocs */
    colindexCount=0;
    rowindexCount=0;
    elementPresent=0; /* flag if there is an element in the current row*/

    for(i = 0; i < (row_size*col_size); i++){
        if((colCount%col_size == 0) && (colCount != 0)){ /* condition used to tell if we are at the end of the row */
            if(elementPresent==1){
                rowStart[rowindexCount] = rowCount;
                rowindexCount++;
            }    
            elementPresent=0;
            rowCount++;
        }
        if(all_elements[i] != 0){
            elementPresent=1;
            nonzeroElements[nonzeroCount] = all_elements[i];
            if(colCount < 10){
                columnIndices[colindexCount] = (colCount)%col_size;
            }
            else{
                columnIndices[colindexCount] = (colCount-1)%col_size;
            }
            nonzeroCount++;
            colindexCount++;
        }
        colCount++;
    }
    if(rowindexCount > 0){ /* adds the total number of rows (last boundary for rowStart) to the end of rowStart */
        rowindexCount++;
        rowStart[rowindexCount-1] = rowCount;
    }

    free(all_elements);
    /* realloc will be used to optimize the matrices to have less data */
    nonzeroElements = (unsigned int *) realloc(nonzeroElements, (sizeof(unsigned int* )) * nonzeroCount);
    columnIndices = (unsigned int *) realloc(columnIndices, (sizeof(unsigned int* )) * colindexCount);
    rowStart = (unsigned int *) realloc(rowStart, (sizeof(unsigned int* )) * rowindexCount);

    
    /* write information to matrix.txt */
    writefile = fopen("matrix.txt", "w");

    fwrite("dimensions", 1, 10,writefile);
    fwrite(" ",sizeof(char),1,writefile);
    fprintf(writefile, "%d %d", row_size, col_size);
    fwrite("\n",1,1,writefile);

    fwrite("values", 1, 6, writefile);
    for(i = 0; i < nonzeroCount; i++){
        fprintf(writefile, " %u", nonzeroElements[i]);
    }
    fwrite("\n",1,1,writefile);

    fwrite("column_indices", 1, 14, writefile);
    for(i = 0; i < colindexCount; i++){
        fprintf(writefile, " %u", columnIndices[i]);
    }
    fwrite("\n",1,1,writefile);

    fwrite("row_start", 1, 9, writefile);
    for(i = 0; i < rowindexCount; i++){
        fprintf(writefile, " %u", rowStart[i]);
    }

    /* free the memory addresses */
    free(nonzeroElements);
    free(columnIndices);
    free(rowStart);


}