/*
Created By: Tomasz Brauntsch
Professor Ding
CS 288-007
October 17, 2023
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

int totalLines = 0;

void traverse(char *pathName ) {/* traverse a directory */
    char * ext;
    struct stat statBuf;
    mode_t mode;
    int result, charsRead;
    DIR *pDir;
    struct dirent *pEnt;
    char fileName[1024];
    FILE * fp;
    char ch;

    result = stat(pathName, &statBuf); /* Obtain file status */
    if ( result == -1 ) { /* Status was not available */
        fprintf( stderr, "Cannot stat %s \n", pathName );
        return;
    }

    mode = statBuf.st_mode; /* Mode of file */
    if(S_ISREG(mode)){ /* Regular file */
        ext = strrchr(pathName, '.'); /* Extracts the extensions */
        if (strcmp(ext, ".txt") == 0){ /* checks the ext and see if it is a .txt file */
            fp = fopen(pathName, "r");
            /* counts the total number of lines */
            while ((ch = fgetc(fp)) != EOF)
            {
                if(ch == '\n')
                    totalLines++;
            }
            fclose(fp);
        }
    }
    else if ( S_ISDIR( mode ) ) { /* Directory */
        pDir=opendir(pathName); /* Open for reading */
    while( (pEnt = readdir(pDir)) != NULL ) {
        if ( strcmp(pEnt->d_name, ".") != 0 &&
            strcmp( pEnt->d_name, "..") != 0) {
            sprintf( fileName, "%s/%s", pathName, pEnt->d_name );
            traverse(fileName);
        }
    }
    closedir(pDir);
    }
}
int main(int argc, char **argv) {
    char * userInput;
    printf("Enter a directory to traverse: ");
    scanf("%s", userInput);

    traverse(userInput);
    printf("The total # of lines: %d\n", totalLines);
    
}