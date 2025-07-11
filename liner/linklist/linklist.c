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
int list_head_insert(listlink H,data_t value){
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
    listlink p = H;
    New->next = p->next;
    p->next = New;
    return 0;
}


int list_pos_insert(listlink H,int pos,data_t value){
    if (H == NULL){
        printf("head is NULL\n");
        return -1;
    }
    listlink New = (listlink)malloc(sizeof(listnode));
    if (New == NULL){
        printf("create new node failed\n");
        return -1;
    }
    if (pos<0){
        printf("pos is invalid!\n");
        return -1;
    }
    New->data = value;
    New->next = NULL;
    listlink pCurrent = H;
    int i =0;
    for(i;i<pos && pCurrent->next != NULL;i++){
    pCurrent = pCurrent->next;
    }
    New->next = pCurrent->next;
    pCurrent->next = New;
    return 0;
}


int list_pos_delet(listlink H,int pos){
    if (H == NULL){
        printf("head is NULL\n");
        return -1;
    }
    if (pos<0){
        printf("pos is invalid!\n");
        return -1;
    }
    listlink pCurrent = H;
    int i =0;
    
}

int list_length(listlink H){
return 
}
