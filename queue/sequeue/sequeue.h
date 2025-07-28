#ifndef SEQUEUE_H
#define SEQUEUE_H
#define MAXSIZE 100

typedef int datatype;
typedef struct {
    datatype data[MAXSIZE];
    int front;
    int rear;
}sequeue;

sequeue* queue_create();
int enqueue(sequeue* sq,datatype x);
datatype dequeue(sequeue* sq);
int queue_empty(sequeue* sq);
int queue_full(sequeue* sq);
sequeue* queue_free(sequeue* sq);
int queue_clear(sequeue* sq);
#endif



