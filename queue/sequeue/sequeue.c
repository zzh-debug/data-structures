#include <stdio.h>
#include <stdlib.h>
#include "sequeue.h"
// 创建队列
sequeue* queue_create() {
    sequeue* sq = (sequeue*)malloc(sizeof(sequeue));
    if (sq == NULL) {
        return NULL;
    }
    sq->front = 0;
    sq->rear = 0;
    return sq;
}

// 入队操作
int enqueue(sequeue* sq, datatype x) {
    if (sq == NULL) {
        return -1;  // 队列不存在
    }
    if ((sq->rear + 1) % MAXSIZE == sq->front) {  // 直接判断队列已满
        return -1;  // 队列已满
    }
    sq->data[sq->rear] = x;
    sq->rear = (sq->rear + 1) % MAXSIZE;  // 循环队列
    return 0;  // 成功
}

// 出队操作
datatype dequeue(sequeue* sq) {
    if (sq == NULL || sq->front == sq->rear) {  // 直接判断队列为空或不存在
        return -1;  // 队列为空或不存在，返回错误值
    }
    datatype temp = sq->data[sq->front];
    sq->front = (sq->front + 1) % MAXSIZE;  // 循环队列
    return temp;
}

// 判断队列是否为空
int queue_empty(sequeue* sq) {
    if (sq == NULL) {
        return 1;  // 队列不存在，视为空
    }
    return sq->front == sq->rear;
}

// 判断队列是否已满
int queue_full(sequeue* sq) {
    if (sq == NULL) {
        return 0;  // 队列不存在，不满
    }
    return (sq->rear + 1) % MAXSIZE == sq->front;
}

// 释放队列内存
sequeue* queue_free(sequeue* sq) {
    if (sq != NULL) {
        free(sq);
        sq = NULL;
    }
    return NULL;
}

// 清空队列
int queue_clear(sequeue* sq) {
    if (sq == NULL) {
        return -1;  // 队列不存在
    }
    sq->front = 0;
    sq->rear = 0;
    return 0;  // 成功
}
