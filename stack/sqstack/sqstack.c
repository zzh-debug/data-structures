#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqstack.h"
sqstack* sqstack_create(int len){
    sqstack* s;
    s = (sqstack*)malloc(sizeof(sqstack));
    if (s == NULL) {
    printf("malloc sqstack failed\n");
    return NULL;
    }
    s->data = (data_t*)malloc(sizeof(data_t)*len);
    if (s->data == NULL) {
        printf("malloc data failed\n");
        free(s);
        return NULL;
    }
    memset(s->data,0,sizeof(data_t)*len);
    s->maxlen = len;
    s->top = -1;
    return s;
}
int stack_push(sqstack* s,data_t value){
    if (s == NULL){
    printf("s is NULL\n");
    return -1;
    }
    if (s->top < s-> maxlen-1) {
        printf("the stack is full\n");
        return -1;
    }
    s->top++;
    s->data[s->top] = value;
    return 0;
}
int stack_pop(sqstack* s){
    if (s == NULL){
    printf("s is NULL\n");
    return -1;
    }
    if (s->top == -1) {
        printf("the stack is empty\n");
        return -1;}
    return (s->data[s->top--]);
}
int stack_top(sqstack* s){
    if (s == NULL){
    printf("s is NULL\n");
    return -1;
    }
    if (s->top == -1) {
        printf("the stack is empty\n");
        return -1;
    }
    return (s->data[s->top]);
}
int stack_clear(sqstack* s){
    if (s == NULL){
    printf("s is NULL\n");
    return -1;
    }
    if (s->top == -1) {
        printf("the stack is empty\n");
        return -1;
    }
    s->top = -1;
    return 0;
}
int stack_free(sqstack* s){
    if (s == NULL){
    printf("s is NULL\n");
    return -1;
    }
    free(s->data);
    free(s);
    return 0;
}
int stack_empty(sqstack* s){
    if (s == NULL){
    printf("s is NULL\n");
    return -1;
    }
   return (s->top == -1 ? 1 : 0);
}
int stack_full(sqstack* s){
    if (s == NULL){
    printf("s is NULL\n");
    return -1;
    }
    return (s->top == s->maxlen-1 ? 1 : 0);
}
