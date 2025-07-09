#ifndef __LINKLIST__H
#define __LINKLIST__H

typedef int data_t;

typedef struct node{
    data_t data;
    struct node* next;
}listnode, *listlink;

listlink list_create();
int list_tail_insert(listlink H,data_t value);


