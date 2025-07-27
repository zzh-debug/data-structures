#include <stdio.h>
#include <stdlib.h>
#include "linkqueue.h"

// 创建队列
linkqueue* queue_create() {
    linkqueue* lq = (linkqueue*)malloc(sizeof(linkqueue));
    if (lq == NULL) {
        return NULL;
    }
    
    // 创建头节点
    listnode* head = (listnode*)malloc(sizeof(listnode));
    if (head == NULL) {
        free(lq);
        return NULL;
    }
    
    head->next = NULL;
    lq->front = head;  // front指向头节点
    lq->rear = head;   // rear也指向头节点（空队列时）
    
    return lq;
}

// 入队操作
int enqueue(linkqueue* lq, datatype x) {
    if (lq == NULL) {
        return -1;
    }
    
    // 创建新节点
    listnode* newnode = (listnode*)malloc(sizeof(listnode));
    if (newnode == NULL) {
        return -1;
    }
    
    newnode->data = x;
    newnode->next = NULL;
    
    // 将新节点链接到队尾
    lq->rear->next = newnode;
    lq->rear = newnode;
    
    return 0;
}

// 出队操作
datatype dequeue(linkqueue* lq) {
    if (lq == NULL || lq->front == lq->rear) {
        printf("队列为空或队列不存在\n");
        return -1; // 错误返回值，实际应用中可能需要更好的错误处理
    }
    
    listnode* temp = lq->front->next; // 要删除的节点（第一个数据节点）
    datatype data = temp->data;
    
    lq->front->next = temp->next;
    
    // 如果删除的是最后一个节点，需要更新rear指针
    if (lq->rear == temp) {
        lq->rear = lq->front;
    }
    
    free(temp);
    return data;
}

// 判断队列是否为空
int queue_empty(linkqueue* lq) {
    if (lq == NULL) {
        return 1; // 队列不存在，视为空
    }
    return lq->front == lq->rear;
}

// 清空队列（保留头节点）
int queue_clear(linkqueue* lq) {
    if (lq == NULL) {
        return -1;
    }
    
    listnode* current = lq->front->next;
    listnode* temp;
    
    // 删除所有数据节点
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    
    // 重置队列为空状态
    lq->front->next = NULL;
    lq->rear = lq->front;
    
    return 0;
}

// 释放整个队列
int queue_free(linkqueue* lq) {
    if (lq == NULL) {
        return -1;
    }
    
    listnode* current = lq->front->next;
    listnode* temp;
    
    // 删除所有数据节点
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    
    // 释放头节点
    free(lq->front);
    
    // 释放队列结构体
    free(lq);
    
    return 0;
}
