#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#define NUM 32
int main()
{
    int i = 0;
    int swt = 0;
    struct Army *a;
    a = (struct Army*)malloc(1 * sizeof(struct Army));
    creat_struct(&a,&i);
    Armies(i, &a);
    do{
        printf("What do you want?\n");
        printf("If delete struct press -- 1\nIf sort struct press -- 2\nIf filter struct press -- 3\nIf create new struct press -- 4\n");
        while(scanf("%i", &swt) != 1 || getchar() != ('\n') || swt > 4 || swt < 1)
        {
            printf("Incorrect number\n");
            printf("Please input number again:");
            rewind(stdin);
        };
        switch (swt) {
            case 1:
                i = del_struct(&a,search_name_struct(&a, i), i);
                Armies(i, &a);
                break;
            case 2:
                sort(a,i);
                Armies(i, &a);
                break;
            case 3:
                filter_by_type(&a,i);
                Armies(i, &a);
                break;
            case 4:
                creat_struct(&a,&i);
                Armies(i, &a);
                break;
        }
    }while(yes());
    free(a);
    return 0;
}