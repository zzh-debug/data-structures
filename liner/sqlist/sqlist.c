#include <stdio.h>
#include "sqlist.h"
#include <stdlib.h>
#include <string.h>
sqlink list_create(){
    sqlink L;
    L = (sqlink)malloc(sizeof(sqlist));
    if(L == NULL){
        printf("list malloc falied\n");
        return L;
    }
    memset(L,0,sizeof(sqlist));
    L->last = -1;
    
    return L;
}

int list_clear(sqlink L){
    if(L==NULL)
        return -1;
    memset(L,0,sizeof(sqlist));
    L->last = -1;
    return 0;
}

int list_empty(sqlink L){
    if(L->last == -1)
        return 1;
    else
        return 0;
}

int list_length(sqlink L){
    if(L == NULL)
        return NULL;
        return(L->last+1);
}
int list_locate(sqlink L,data_t value){
    return 0;

}
int list_insert(sqlink L,data_t value,int pos){
    int i;
    if(L->last == N-1){
        printf("list is full\n");
        return -1;
    }
    if(pos < 0 || pos > L->last+1){
    printf("Pos is invalid\n");
    return -1;
    }
    for(i = L->last; i >= pos; i++){
    L->data[i+1] = L->data[i];
    }
    L->data[pos] = value;
    L->last++;

    return 0;

}




