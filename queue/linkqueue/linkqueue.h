#ifndef LINKQUEUE_H
#define LINKQUEUE_H

typedef int datatype;
typedef struct node {
    datatype data;
    struct node* next;
}listnode,*linklist;

typedef struct {
    linklist front;
    linklist rear;
}linkqueue;

linkqueue* queue_create();
int enqueue(linkqueue* lq,datatype x);
datatype dequeue(linkqueue* lq);
int queue_empty(linkqueue* lq);
int queue_clear(linkqueue* lq);
int queue_free(linkqueue* lq);

#endif
