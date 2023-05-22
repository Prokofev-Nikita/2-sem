#ifndef ARMY_FUNC_H
#define ARMY_FUNC_H
enum type {
    Air_Force = 1,
    Marines,
    Navy,
    Infantry
};

struct Army
{
    char name[50];
    int n_employee;
    int vehicles;
    enum type Type;
};

char* getsStr();
int compare_name (const struct Army *a,const struct Army *b);
int compare_employee(const struct Army *a,const struct  Army *b);
int compare_vehicles(const struct Army *a,const struct  Army *b);
int compare_type(const struct Army *a,const struct  Army *b);
void filter_by_Air_Force(struct Army **a,int n);
void filter_by_Marines(struct Army **a,int n);
void filter_by_Navy(struct Army **a, int n);
void filter_by_Infantry (struct Army **a,int n);
void filter_by_type(struct Army **a,int n);
void info(int i, struct Army **a);
void type_army(enum type i);
int yes();
void Armies(int n, struct Army **a);
int del_struct (struct Army **a,int j, int n);
int search_name_struct(struct Army **a,int n);
void creat_struct (struct Army **a,int *n);
int second_sort(int (*compareTypes[4]) (const struct Army*,const struct Army*),const struct Army* a,const struct Army* b);
void sort(struct Army * arr, int size);
#endif
