#ifndef __SQLIST_H
#define __SQLIST_H

#define N 128
typedef int data_t;

typedef struct sqlist{
    data_t data[N];
    int last;    
}sqlist,*sqlink;

sqlink list_create();
int list_clear(sqlink L);
int list_empty(sqlink L);
int list_length(sqlink L);
int list_locate(sqlink L,data_t value);
int list_insert(sqlink L,data_t value,int pos);
#endif


