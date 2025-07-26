#include <stdio.h>
#include "linkqueue.h"

void print_queue_status(linkqueue* lq) {
    if (queue_empty(lq)) {
        printf("队列状态: 空\n");
    } else {
        printf("队列状态: 非空\n");
    }
    printf("------------------------\n");
}

int main() {
    printf("=== 链式队列测试程序 ===\n\n");
    
    // 创建队列
    linkqueue* lq = queue_create();
    if (lq == NULL) {
        printf("队列创建失败!\n");
        return -1;
    }
    printf("队列创建成功!\n");
    print_queue_status(lq);
    
    // 测试入队操作
    printf("1. 测试入队操作:\n");
    printf("入队元素: 10, 20, 30\n");
    enqueue(lq, 10);
    enqueue(lq, 20);
    enqueue(lq, 30);
    print_queue_status(lq);
    
    // 测试出队操作
    printf("2. 测试出队操作:\n");
    printf("出队元素: %d\n", dequeue(lq));
    printf("出队元素: %d\n", dequeue(lq));
    print_queue_status(lq);
    
    // 继续入队
    printf("3. 继续入队测试:\n");
    printf("入队元素: 40, 50\n");
    enqueue(lq, 40);
    enqueue(lq, 50);
    print_queue_status(lq);
    
    // 测试队列清空
    printf("4. 测试队列清空:\n");
    printf("出队元素: %d\n", dequeue(lq));
    printf("出队元素: %d\n", dequeue(lq));
    printf("出队元素: %d\n", dequeue(lq));
    print_queue_status(lq);
    
    // 测试空队列出队
    printf("5. 测试空队列出队:\n");
    dequeue(lq);  // 应该输出错误信息
    
    // 测试清空功能
    printf("\n6. 测试queue_clear功能:\n");
    enqueue(lq, 100);
    enqueue(lq, 200);
    printf("入队两个元素后:\n");
    print_queue_status(lq);
    
    queue_clear(lq);
    printf("调用queue_clear后:\n");
    print_queue_status(lq);
    
    // 清空后再次入队测试
    printf("7. 清空后再次入队测试:\n");
    enqueue(lq, 300);
    printf("入队元素: 300\n");
    print_queue_status(lq);
    printf("出队元素: %d\n", dequeue(lq));
    
    // 释放队列
    printf("\n8. 释放队列\n");
    if (queue_free(lq) == 0) {
        printf("队列释放成功!\n");
    }
    
    printf("\n=== 测试完成 ===\n");
    return 0;
}
