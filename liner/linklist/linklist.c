#include <stdio.h>
#include "linklist.h"
#include <stdlib.h>

listlink list_create(){
    listlink H = NULL;
    H = (listlink)malloc(sizeof(listnode));
    if(H == NULL){
        printf("malloc failed\n");
        return H;
    }
    H->data = 0;
    H->next = NULL;
    return H;
}
int list_tail_insert(listlink H,data_t value){
    if (H == NULL){
        printf("head is NULL\n");
        return -1;
    }
    listlink New = (listlink)malloc(sizeof(listnode));
    if (New == NULL){
        printf("create new node failed\n");
        return -1;
    }
    New->data = value;
    New->next = NULL;
    listlink p = H;
    while (p->next != NULL){
        p = p->next;
    }
    p->next = New;
    return 0;
}

int list_show(listlink H){
    if (H == NULL){
        printf("head is NULL\n");
        return -1;
    }
    listlink p = H->next;
    while (p != NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}


void list_free(listlink H){
    if (H == NULL){
        printf("head is NULL\n");
        return;
    }
    listlink p = H;
    while (p !=NULL){
    listlink temp = p;
    p = p->next;
    free(temp);
    }
    return;
}
