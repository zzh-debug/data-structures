#ifndef __SQSTACK__H
#define __SQSTACK__H

typedef int data_t;
typedef struct {
    data_t* data;
    int maxlen;
    int top;
}sqstack;

sqstack* sqstack_create(int len);
int stack_push(sqstack* s,data_t value);
int stack_pop(sqstack* s);
int stack_top(sqstack* s);
int stack_clear(sqstack* s);
int stack_free(sqstack* s);
int stack_empty(sqstack* s);
int stack_full(sqstack* s);
#endif
