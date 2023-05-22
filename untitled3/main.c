#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "func.h"

int main() {
    FILE* fp = fopen("dns.txt","r+");
    LRUCache *cache = createCache(6);
    do {
        printf("Если вы хотите вывести кэш -- введите 1!\n");
        printf("Если вы хотите произвести поиск в DNS-файле по типу 1 -- введите 2!\n");
        printf("Если вы хотите произвести поиск в DNS-файле по типу 2 -- введите 3!\n");
        printf("Если вы хотите добавить запись по типу 1 в DNS-файл-- введите 4!\n");
        printf("Если вы хотите добавить запись по типу 2 в DNS-файл-- введите 5!\n");
        printf("Если вы хотите выйти из программы -- введите 6!\n");
        u_int8_t type = 0;
        while(scanf("%i", &type) != 1 || type > 6 || type < 1){
            printf("Такого варианта нет,введите ещё раз!\n");
            int ch;
            while ((ch = getchar()) != EOF && ch != '\n');
        }
        switch (type) {
            case 1:
            {
                printCache(cache);
                break;
            }
            case 2:
            {
                char key[126];
                printf("Введите имя Домена:\n");
                scanf("%s",key);
                searchAndPrint(cache,fp,key,1);
                break;
            }
            case 3:
            {
                char key[126];
                printf("Введите имя Домена:\n");
                scanf("%s",key);
                searchAndPrint(cache,fp,key,2);
                break;
            }
            case 4:
            {
                putInFile(fp,1);
                break;
            }
            case 5:
            {
                putInFile(fp,2);
                break;
            }
            case 6:
            {
                freeCache(cache);
                fclose(fp);
                return 0;
            }
        }
    }while(1);
}