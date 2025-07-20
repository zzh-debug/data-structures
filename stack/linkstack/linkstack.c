#include <stdio.h>
#include <stdlib.h>
#include "linkstack.h"

linkstack stack_create() {
    linkstack head = (linkstack)malloc(sizeof(listnode));
    if (head == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    head->next = NULL;
    return head;
}
int stack_push(linkstack s,data_t value) {
    if (s == NULL) {
        printf("Stack not initialized!\n");
        return -1;
    }
    
    // 创建新节点
    linkstack new_node = (linkstack)malloc(sizeof(listnode));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }
    // 设置数据和指针
    new_node->data = value;
    new_node->next = s->next;
    s->next = new_node;
    return 0;
}
data_t stack_pop(linkstack s) {
    if (s == NULL || s->next == NULL) {
        printf("Stack is empty or not initialized!\n");
        return -1;  // 返回错误值
    }
    
    linkstack top_node = s->next;  // 获取栈顶节点
    data_t value = top_node->data; // 获取栈顶数据
    
    s->next = top_node->next;  // 头节点指向下一个节点
    free(top_node);            // 释放栈顶节点
    
    return value;
}
int stack_empty(linkstack s) {
    if (s == NULL) {
        printf("Stack not initialized!\n");
        return -1;
    }
    return (s->next == NULL) ? 1 : 0;  // 1表示空，0表示非空
}
data_t stack_top(linkstack s) {
    if (s == NULL || s->next == NULL) {
        printf("Stack is empty or not initialized!\n");
        return -1;  // 返回错误值
    }
    
    return s->next->data;  // 返回栈顶数据
}
int stack_free(linkstack s) {
    if (s == NULL) {
        printf("Stack not initialized!\n");
        return -1;
    }
    while (s->next != NULL) {
        linkstack temp = s->next;
        s->next = temp->next;
        free(temp);
    }
    free(s);
    return 0;
}

