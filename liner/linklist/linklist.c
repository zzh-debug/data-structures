#include <stdio.h>
#include "linklist.h"
#include <stdlib.h>

listlink list_create(){
    listlink H = NULL;             // 设置H为头节点
    H = (listlink)malloc(sizeof(listnode));
    if(H == NULL){
        printf("malloc failed\n");
        return H;
    }
    H->data = 0;                  //头节点不设置有效值，故称为哑头节点
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
    listlink p = H;                //保证头节点不动，设置新指针p进行指针滑动，遍历到尾部进行插入
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
    listlink temp = p;   //设置temp节点用于保存需要释放的节点的位置
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
    New->next = H->next;
    H->next = New;
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
    for(i;i<pos && pCurrent->next != NULL;i++){ //pos大于链表长度进行尾部插入
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
    int length = list_length(H);
    if (pos<0 || pos>length){
        printf("pos is invalid!\n");
        return -1;
    }
    listlink pCurrent = H;
    for (int i = 0;i < pos;i++){
        pCurrent = pCurrent->next;
    }
    listlink toDelet = pCurrent->next;
    pCurrent->next = toDelet->next;
    free(toDelet);
    return 0;
}

int list_length(listlink H){
    if (H == NULL){
        printf("head is NULL\n");
        return -1;
    }
    int length = 0;
    listlink pCurrent = H;
    while (pCurrent->next != NULL){
        pCurrent = pCurrent->next;
        length++;
    }
    return length;
}
int list_reverse(listlink H){
    if (H == NULL || H->next == NULL){
        return 0;
    }
    listlink prev = H->next;
    if (prev->next == NULL){
        return 0;
    }
    listlink curr = prev->next;
    prev->next = NULL;
    listlink next = NULL;
    while (curr!= NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    H->next = prev;
    return 0;
}
