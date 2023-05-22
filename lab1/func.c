#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"
#define NUM 32

char* getsStr()
{
    char* str = (char*)calloc(NUM, sizeof(char));
    char ch;
    int pos = 0;
    do
    {
        ch = getchar();
        if (ch == '\n')
        {
            str[pos] = '\0';
            str = (char*)realloc(str, (pos + 1) * sizeof(char));
            return str;
        }

        str[pos] = ch;
        pos++;
        if (pos == 32)
            str = (char*)realloc(str, (pos + 1) * sizeof(char));
    } while (ch != '\0');
}

int compare_name (const struct Army *a,const struct Army *b){
    return strcmp(a->name, b->name);
}

int compare_employee(const struct Army *a,const struct  Army *b){
    return a->n_employee - b->n_employee;
}

int compare_vehicles(const struct Army *a,const struct  Army *b){
    return a->vehicles - b->vehicles;
}

int compare_type(const struct Army *a,const struct  Army *b) {
    return a->Type - b->Type;
}

void filter_by_Air_Force(struct Army **a,int n) {
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if ((*a)[j].Type > (*a)[j + 1].Type && (*a)[j + 1].Type == 1) {
                struct Army tmp = (*a)[j];
                (*a)[j] = (*a)[j + 1];
                (*a)[j + 1] = tmp;
            }
            if ((*a)[j].Type == (*a)[j + 1].Type && (*a)[j].Type == 1 && (*a)[j].n_employee > (*a)[j + 1].n_employee) {
                struct Army tmp = (*a)[j];
                (*a)[j] = (*a)[j + 1];
                (*a)[j + 1] = tmp;
            }
        }
    }
}

void filter_by_Marines(struct Army **a,int n){
    for (int i = n; i >= 0; i--) {
        for (int j = 1; j < i; j++) {
            if (((*a)[j].Type > (*a)[j - 1].Type || (*a)[j].Type < (*a)[j - 1].Type ) && (*a)[j].Type == 2 ) {
                struct Army tmp = (*a)[j];
                (*a)[j] = (*a)[j - 1];
                (*a)[j - 1] = tmp;
            }
            if ((*a)[j].Type == (*a)[j - 1].Type && (*a)[j].n_employee > (*a)[j - 1].n_employee && (*a)[i].Type == 2)
            {
                struct Army tmp = (*a)[j];
                (*a)[j] = (*a)[j - 1];
                (*a)[j - 1] = tmp;
            }
        }
    }
}

void filter_by_Navy(struct Army **a, int n){
    for (int i = n; i >= 0; i--) {
        for (int j = 1; j < i; j++) {
            if (((*a)[j].Type > (*a)[j - 1].Type || (*a)[j].Type < (*a)[j - 1].Type ) && (*a)[j].Type == 3 ) {
                struct Army tmp = (*a)[j];
                (*a)[j] = (*a)[j - 1];
                (*a)[j - 1] = tmp;
            }
            if ((*a)[j].Type == (*a)[j - 1].Type && (*a)[j].n_employee > (*a)[j - 1].n_employee && (*a)[i].Type == 3)
            {
                struct Army tmp = (*a)[j];
                (*a)[j] = (*a)[j - 1];
                (*a)[j - 1] = tmp;
            }
        }
    }
}

void filter_by_Infantry (struct Army **a,int n){
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if ((*a)[j].Type < (*a)[j + 1].Type && (*a)[j + 1].Type == 4) {
                struct Army tmp = (*a)[j];
                (*a)[j] = (*a)[j + 1];
                (*a)[j + 1] = tmp;
            }
            if ((*a)[j].Type == (*a)[j + 1].Type && (*a)[j].Type == 4 && (*a)[j].n_employee > (*a)[j + 1].n_employee)
            {
                struct Army tmp = (*a)[j];
                (*a)[j] = (*a)[j + 1];
                (*a)[j + 1] = tmp;
            }
        }
    }
}

void filter_by_type(struct Army **a,int n){
    int k = 0;
    printf("By what type are you going to filter?\n");
    printf("If you have to go first Air Force press -- 1\nIf you have to go first Marines press -- 2\nIf you have to go first Navy press -- 3\nIf you have to go first Infantry press -- 4\n");
    while(scanf("%i", &k) != 1 || getchar() != '\n' || k > 4 || k < 1){
        printf("Incorrect number!\nPlease input number again:");
        rewind(stdin);
    }
    switch (k) {
        case 1:{
            filter_by_Air_Force(&(*a), n);
            break;
        }
        case 2:{
            filter_by_Marines(&(*a), n);
            break;
        }
        case 3:{
            filter_by_Navy(&(*a), n);
            break;
        }
        case 4:{
            filter_by_Infantry(&(*a), n);
            break;
        }
    }
}

void info(int i, struct Army **a){

    printf("Enter name:");
    while(strlen(gets((*a)[i].name)) > 50 ){
        printf("Very long name!\nPlease input correct Name:");
        rewind(stdin);
    };
    printf("Enter number of soldiers:");
    rewind(stdin);
    while(scanf("%i", &((*a)[i].n_employee)) != 1 || getchar() != ('\n') || (*a)[i].n_employee < 0 || (*a)[i].n_employee > 2000000)
    {
        printf("Incorrect number\n");
        printf("Please input number again:");
        rewind(stdin);
    };
    printf("Enter number of warmachines:");
    while(scanf("%i", &((*a)[i].vehicles)) != 1 || getchar() != ('\n') || (*a)[i].vehicles < 0 || (*a)[i].vehicles > 250000)
    {
        printf("Incorrect number\n");
        printf("Please input number again:");
        rewind(stdin);
    };
    printf("Type of Force\n1 -- Air Force\n2 --Marines\n3 -- Navy\n4 -- Infantry\n");
    while(scanf("%i", &((*a)[i].Type)) != 1 || getchar() != ('\n') || (*a)[i].Type < 1 || (*a)[i].Type > 4)
    {
        printf("Incorrect number\n");
        printf("Please input number again:");
        rewind(stdin);
    };

}

void type_army(enum type i){
    switch (i) {
        case 1:
            printf("Air Force\n");
            break;
        case 2:
            printf("Marines\n");
            break;
        case 3:
            printf("Navy\n");
            break;
        case 4:
            printf("Infantry\n");
            break;
    }
}

int yes()
{
    int k;
    printf("Do you want continue\nIf yes press -- 1\n If no press --0\n");
    while(scanf("%i", &k) != 1 || getchar() != ('\n') || k > 1 || k < 0){
        printf("Incorrect number\n");
        printf("Please input number again:");
        rewind(stdin);
    }
    rewind(stdin);
    return k;
}

void Armies(int n, struct Army **a) {
    for (int i = 0; i < n; i++) {
        printf("\n%s\nNumber of soldiers:%i\nNumber of warmachines:%i\n", (*a)[i].name, (*a)[i].n_employee, (*a)[i].vehicles);
        type_army((*a)[i].Type);
    }
}

int del_struct (struct Army **a,int j, int n){

    for (int i = j; i < n; i++ ){
        (*a)[i] = (*a)[i + 1];
    }
    (*a) = realloc(*a,(--n) * sizeof(struct Army));
    return n;
}

int search_name_struct(struct Army **a,int n){
    printf("Please enter name of struct:");
    int k = 1;
    do {
        char* name = getsStr();
        for (int i = 0; i < n; i++) {
            if (strcmp(name, (*a)[i].name) == 0) {
                return i;
            }
        }
        printf("\nThis name does not exist!\nIf you want to exit the program -- press 0!\n");
        printf("If you want continue enter name again:");
        scanf("%i",&k);
    }while(k);
}

void creat_struct (struct Army **a,int *n){
    do
    {
        info((*n), a);
        (*n)++;
        (*a) = realloc((*a),((*n) + 1) * sizeof(struct Army));
    }while(yes());
}

int second_sort(int (*compare_types[4]) (const struct Army*,const struct Army*),const struct Army* a,const struct Army* b) {
    int comp = 0;
    for(int i = 0; i < 2; i++) {
        if(compare_types[i] == NULL || comp != 0) break;
        comp = ((*compare_types[i])(a, b));
    }
    return comp;
}

void sort(struct Army * arr, int size) {
    int (*compare_types[4]) (const struct Army*, const struct Army*) = {&compare_name, &compare_employee,&compare_vehicles,&compare_type};
    int count;
    printf("Choose sort count: ");
    while(!scanf("%d", &count) || count < 1 || count > 11) {
        printf("Invalid sort count!\n");
        rewind(stdin);
        printf("Choose sort count: ");
    }
    printf("0 - Name\n"
           "1 - Count of Employee\n"
           "2 - Count of Vehicles\n"
           "3 - Type\n");
    int (*second_types[4]) (const struct Army*,const struct Army*);
    for(int i = 0; i < count; i++) {
        int ss;
        printf("Choose sort type: ");
        while(!scanf("%d", &ss) || ss < 0 || ss > 3) {
            printf("Invalid sort type!\n");
            rewind(stdin);
            printf("Choose second sort type: ");
        }
        second_types[i] = compare_types[ss];
    }
    for(int i = count; i < 2; i++) {
        second_types[i] = NULL;
    }

    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            int comp = second_sort(second_types, &arr[j], &arr[j + 1]);
            if(comp > 0) {
                struct Army tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

