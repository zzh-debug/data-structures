#include <stdio.h>
#include "sequeue.h"

// 打印队列状态（用于调试）
void print_queue_status(sequeue* sq) {
    if (sq == NULL) {
        printf("队列不存在\n");
        return;
    }
    printf("队列状态: front=%d, rear=%d, 空=%s, 满=%s\n", 
           sq->front, sq->rear,
           queue_empty(sq) ? "是" : "否",
           queue_full(sq) ? "是" : "否");
}

// 测试基本创建和销毁
void test_create_destroy() {
    printf("\n=== 测试1: 队列创建和销毁 ===\n");
    
    sequeue* q = queue_create();
    if (q != NULL) {
        printf("✓ 队列创建成功\n");
        print_queue_status(q);
    } else {
        printf("✗ 队列创建失败\n");
        return;
    }
    
    q = queue_free(q);
    if (q == NULL) {
        printf("✓ 队列销毁成功\n");
    } else {
        printf("✗ 队列销毁失败\n");
    }
}

// 测试基本入队出队
void test_basic_operations() {
    printf("\n=== 测试2: 基本入队出队 ===\n");
    
    sequeue* q = queue_create();
    
    // 测试空队列
    printf("初始状态: ");
    print_queue_status(q);
    
    // 入队测试
    printf("\n入队操作:\n");
    for (int i = 1; i <= 5; i++) {
        if (enqueue(q, i * 10) == 0) {
            printf("✓ 入队 %d 成功\n", i * 10);
        } else {
            printf("✗ 入队 %d 失败\n", i * 10);
        }
        print_queue_status(q);
    }
    
    // 出队测试
    printf("\n出队操作:\n");
    while (!queue_empty(q)) {
        int value = dequeue(q);
        printf("✓ 出队: %d\n", value);
        print_queue_status(q);
    }
    
    // 测试空队列出队
    printf("\n空队列出队测试:\n");
    int result = dequeue(q);
    printf("空队列出队结果: %d (应该是-1)\n", result);
    
    q = queue_free(q);
}

// 测试队列满的情况
void test_full_queue() {
    printf("\n=== 测试3: 队列满测试 ===\n");
    
    sequeue* q = queue_create();
    
    // 尝试填满队列 (记住实际容量是MAXSIZE-1)
    printf("尝试填满队列:\n");
    int count = 0;
    for (int i = 1; i <= 101; i++) {  // 超过MAXSIZE
        if (enqueue(q, i) == 0) {
            count++;
        } else {
            printf("✗ 第%d个元素入队失败，队列已满\n", i);
            break;
        }
    }
    
    printf("✓ 成功入队 %d 个元素\n", count);
    print_queue_status(q);
    
    // 测试满队列继续入队
    printf("\n尝试向满队列入队:\n");
    if (enqueue(q, 999) == -1) {
        printf("✓ 满队列拒绝入队，测试通过\n");
    } else {
        printf("✗ 满队列接受了入队，测试失败\n");
    }
    
    q = queue_free(q);
}

// 测试循环队列特性
void test_circular_queue() {
    printf("\n=== 测试4: 循环队列特性 ===\n");
    
    sequeue* q = queue_create();
    
    // 先入队5个元素
    printf("初始入队5个元素:\n");
    for (int i = 1; i <= 5; i++) {
        enqueue(q, i);
        printf("入队 %d, ", i);
        print_queue_status(q);
    }
    
    // 出队3个元素
    printf("\n出队3个元素:\n");
    for (int i = 0; i < 3; i++) {
        int value = dequeue(q);
        printf("出队 %d, ", value);
        print_queue_status(q);
    }
    
    // 再入队几个元素，测试循环特性
    printf("\n再入队几个元素（测试循环）:\n");
    for (int i = 6; i <= 10; i++) {
        if (enqueue(q, i) == 0) {
            printf("入队 %d, ", i);
            print_queue_status(q);
        } else {
            printf("入队 %d 失败\n", i);
        }
    }
    
    // 清空队列
    printf("\n清空队列:\n");
    while (!queue_empty(q)) {
        printf("%d ", dequeue(q));
    }
    printf("\n");
    print_queue_status(q);
    
    q = queue_free(q);
}

// 测试队列清空功能
void test_clear_queue() {
    printf("\n=== 测试5: 队列清空功能 ===\n");
    
    sequeue* q = queue_create();
    
    // 入队一些元素
    for (int i = 1; i <= 5; i++) {
        enqueue(q, i * 100);
    }
    
    printf("清空前: ");
    print_queue_status(q);
    
    // 清空队列
    if (queue_clear(q) == 0) {
        printf("✓ 队列清空成功\n");
    } else {
        printf("✗ 队列清空失败\n");
    }
    
    printf("清空后: ");
    print_queue_status(q);
    
    // 测试清空后能否正常使用
    printf("\n清空后重新使用:\n");
    enqueue(q, 888);
    enqueue(q, 999);
    
    printf("重新入队后: ");
    print_queue_status(q);
    
    printf("出队: %d %d\n", dequeue(q), dequeue(q));
    
    q = queue_free(q);
}

// 测试错误处理
void test_error_handling() {
    printf("\n=== 测试6: 错误处理 ===\n");
    
    // 测试空指针操作
    printf("测试空指针操作:\n");
    
    if (enqueue(NULL, 10) == -1) {
        printf("✓ 空指针入队正确返回错误\n");
    }
    
    if (dequeue(NULL) == -1) {
        printf("✓ 空指针出队正确返回错误\n");
    }
    
    if (queue_empty(NULL) == 1) {
        printf("✓ 空指针判空正确返回真\n");
    }
    
    if (queue_full(NULL) == 0) {
        printf("✓ 空指针判满正确返回假\n");
    }
    
    if (queue_clear(NULL) == -1) {
        printf("✓ 空指针清空正确返回错误\n");
    }
    
    // 测试释放空指针
    sequeue* null_queue = NULL;
    null_queue = queue_free(null_queue);  // 应该安全处理
    printf("✓ 释放空指针安全处理\n");
}

int main() {
    printf("开始测试循环队列...\n");
    
    test_create_destroy();
    test_basic_operations();
    test_full_queue();
    test_circular_queue();
    test_clear_queue();
    test_error_handling();
    
    printf("\n所有测试完成！\n");
    return 0;
}
