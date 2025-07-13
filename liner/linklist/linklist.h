#ifndef __LINKLIST__H
#define __LINKLIST__H

typedef int data_t;

typedef struct node{
    data_t data;
    struct node* next;
}listnode, *listlink;

listlink list_create();
int list_tail_insert(listlink H,data_t value);
int list_show(listlink H);
void list_free(listlink H);
int list_head_insert(listlink H,data_t value);
int list_pos_insert(listlink H,int pos,data_t value);
int list_pos_delet(listlink H,int pos);
int list_length(listlink H);
int list_reverse(listlink H);
#endif 
