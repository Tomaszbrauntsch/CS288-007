/*
Created By: Tomasz Brauntsch
Professor Ding
CS 288-007
October 17, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hexing(unsigned char*, int);

int main() {
    int i, fileSize;
    unsigned char * allBytes;
    unsigned int currByte;
    FILE *bytesFile = fopen("matrix.bin", "rb");
    if (bytesFile == NULL) {
        perror("fopen");
    }

    /* Acquires the filesize*/
    fseek(bytesFile, 0L, SEEK_END);
    fileSize = ftell(bytesFile);
    rewind(bytesFile);

    /* mallocs based off the size of the filesize */
    allBytes = (unsigned char *) malloc((fileSize/4) * sizeof(unsigned char *));
    fread(allBytes, 4, (fileSize/4), bytesFile);
    for (i = 0; i <= (fileSize/4); i+=4) {
        hexing(allBytes,i);
    }

    fclose(bytesFile);
    free(allBytes);
    return 0;
}

void hexing(unsigned char * myBytes, int iterator){
    /* the binary operator for the decimal portion, moves the bytes to create a 4 byte hex address then printf prints it as a unsigned int */
    printf("Integer: Hex: 0x%02x%02x%02x%02x Dec:%u\n",myBytes[iterator], myBytes[iterator+1], myBytes[iterator+2], myBytes[iterator+3], ((myBytes[iterator] << 24) | (myBytes[iterator+1] << 16) | (myBytes[iterator+2]) << 8 | (myBytes[iterator+3])));
    printf("Byte 1: Hex: 0x%02x Char: ", myBytes[iterator]);
    if(isprint((int)myBytes[iterator])!=0){
        printf("%c", (int)myBytes[iterator]);
    }
    else{
        printf("\\%u", (int)myBytes[iterator]);
    }
    printf("\n");

    printf("Byte 2: Hex: 0x%02x Char: ", myBytes[iterator+1]);
    if(isprint((int)myBytes[iterator+1])!=0){
        printf("%c", (int)myBytes[iterator+1]);
    }
    else{
        printf("\\%u", (int)myBytes[iterator+1]);
    }
    printf("\n");

    printf("Byte 3: Hex: 0x%02x Char: ", myBytes[iterator+2]);
    if(isprint((int)myBytes[iterator+2])!=0){
        printf("%c", (int)myBytes[iterator+2]);
    }
    else{
        printf("\\%u", (int)myBytes[iterator+2]);
    }
    printf("\n");

    printf("Byte 4: Hex: 0x%02x Char: ", myBytes[iterator+3]);
    if(isprint((int)myBytes[iterator+3])!=0){
        printf("%c", (int)myBytes[iterator+3]);
    }
    else{
        printf("\\%u", (int)myBytes[iterator+3]);
    }
    printf("\n");
    printf("\n");
}