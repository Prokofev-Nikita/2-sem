#include <stdio.h>
#include "BMP_Read.h"

#define SIZE_FILE_NAME 32



    int main(){
    printf("Write name of the previous file\n");
    char name[SIZE_FILE_NAME];
        scanf("%s",&name);
   BMPFile* bmpFile = loadBMPFile(name);
   printBMPInfo(bmpFile);
   printf("Write name of the new file\n");
   char newName[SIZE_FILE_NAME];
   scanf("%s",&newName);
   FILE* NewFile = fopen(newName,"wb");
   int type = 2;
   printf("Choose functions\n");
        printf("Negative -- press 1\n");
        printf("White/Black -- press 2\n");
        printf("Gamma Correction -- press 3\n");
        printf("Median filter -- press 4\n");
   while(scanf("%i",&type) != 1 || type > 4 || type < 1) {
       printf("This functions not exist\n");
       printf("Choose again!\n");
       int ch = 0;
       while ((ch = getchar()) != EOF && ch != '\n');
   }
        writeBMPFile(bmpFile,NewFile,type);
   fclose(NewFile);
   freeBMPFile(bmpFile);
    return 0;
}