// sqstack.h
#ifndef SQSTACK_H
#define SQSTACK_H

#include <stdbool.h>

// 栈中存储的数据类型，可以根据需要修改
typedef int data_t;

/**
 * 栈操作的返回状态枚举
 * 用于明确区分不同类型的错误，提高代码可读性和调试能力
 */
typedef enum {
    STACK_SUCCESS = 0,                  // 操作成功
    STACK_ERROR_NULL_POINTER = -1,      // 空指针错误
    STACK_ERROR_MEMORY_ALLOCATION = -2, // 内存分配失败
    STACK_ERROR_STACK_FULL = -3,        // 栈已满
    STACK_ERROR_STACK_EMPTY = -4,       // 栈为空
    STACK_ERROR_INVALID_SIZE = -5       // 无效的大小参数
} stack_result_t;

/**
 * 顺序栈结构体定义
 */
typedef struct {
    data_t* data;    // 指向动态分配的数组，存储栈中的元素
    int maxlen;      // 栈的最大容量
    int top;         // 栈顶索引，-1表示空栈
} sqstack_t;

// ============== 栈的基本操作函数声明 ==============

/**
 * 创建一个指定容量的栈
 * @param len 栈的初始容量
 * @return 成功返回栈的指针，失败返回NULL
 */
sqstack_t* sqstack_create(int len);

/**
 * 销毁栈，释放所有相关内存
 * @param s 要销毁的栈指针
 * @return 操作结果状态码
 */
stack_result_t sqstack_destroy(sqstack_t* s);

/**
 * 向栈顶压入一个元素
 * @param s 栈指针
 * @param value 要压入的值
 * @return 操作结果状态码
 */
stack_result_t sqstack_push(sqstack_t* s, data_t value);

/**
 * 从栈顶弹出一个元素（删除并返回栈顶元素）
 * @param s 栈指针
 * @param value 用于接收弹出值的指针（输出参数）
 * @return 操作结果状态码
 */
stack_result_t sqstack_pop(sqstack_t* s, data_t* value);

/**
 * 查看栈顶元素但不删除
 * @param s 栈指针
 * @param value 用于接收栈顶值的指针（输出参数）
 * @return 操作结果状态码
 */
stack_result_t sqstack_top(sqstack_t* s, data_t* value);

/**
 * 清空栈（逻辑清空，不释放内存）
 * @param s 栈指针
 * @return 操作结果状态码
 */
stack_result_t sqstack_clear(sqstack_t* s);

// ============== 栈的查询函数声明 ==============

/**
 * 检查栈是否为空
 * @param s 栈指针（const表示不会修改栈）
 * @return true表示空栈，false表示非空
 */
bool sqstack_is_empty(const sqstack_t* s);

/**
 * 检查栈是否已满
 * @param s 栈指针（const表示不会修改栈）
 * @return true表示已满，false表示未满
 */
bool sqstack_is_full(const sqstack_t* s);

/**
 * 获取栈中当前元素个数
 * @param s 栈指针（const表示不会修改栈）
 * @return 元素个数，失败返回-1
 */
int sqstack_size(const sqstack_t* s);

/**
 * 获取栈的最大容量
 * @param s 栈指针（const表示不会修改栈）
 * @return 最大容量，失败返回-1
 */
int sqstack_capacity(const sqstack_t* s);

// ============== 高级功能函数声明 ==============

/**
 * 动态调整栈的容量
 * @param s 栈指针
 * @param new_capacity 新的容量大小
 * @return 操作结果状态码
 */
stack_result_t sqstack_resize(sqstack_t* s, int new_capacity);

#endif

// sqstack.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqstack.h"

// ============== 常量定义 ==============
#define MIN_STACK_SIZE 1        // 栈的最小容量
#define DEFAULT_STACK_SIZE 10   // 当用户传入无效参数时使用的默认容量

// ============== 内部辅助函数 ==============

/**
 * 检查栈指针的有效性（内部函数）
 * static: 仅在当前文件内可见，避免命名冲突
 * inline: 建议编译器内联展开，提高性能
 * 
 * @param s 要检查的栈指针
 * @return true表示栈有效，false表示栈无效
 */
static inline bool is_valid_stack(const sqstack_t* s) {
    // 三重检查确保栈的完整性：
    // 1. 栈指针本身不能为NULL
    // 2. 栈的数据区域指针不能为NULL  
    // 3. 栈的容量必须大于0
    return (s != NULL && s->data != NULL && s->maxlen > 0);
}

// ============== 栈的基本操作函数实现 ==============

/**
 * 创建一个指定容量的栈
 */
sqstack_t* sqstack_create(int len) {
    // 第一步：参数有效性检查和修正
    if (len <= 0) {
        // 如果用户传入无效值（0或负数），自动使用默认值
        // 这是容错设计，提高函数的健壮性
        len = DEFAULT_STACK_SIZE;
    }
    
    // 第二步：分配栈结构体内存
    sqstack_t* s = (sqstack_t*)malloc(sizeof(sqstack_t));
    if (s == NULL) {
        // 内存分配失败，输出错误信息并返回NULL
        fprintf(stderr, "Error: Failed to allocate memory for stack structure\n");
        return NULL;
    }
    
    // 第三步：分配栈数据数组内存
    s->data = (data_t*)malloc(sizeof(data_t) * len);
    if (s->data == NULL) {
        // 数据数组分配失败，需要释放已分配的结构体内存
        // 避免内存泄漏
        fprintf(stderr, "Error: Failed to allocate memory for stack data\n");
        free(s);  // 释放第二步分配的内存
        return NULL;
    }
    
    // 第四步：初始化栈的属性
    // 注意：不需要用memset初始化数据数组，因为栈的未使用部分不应该被访问
    s->maxlen = len;    // 设置最大容量
    s->top = -1;        // 初始化为空栈（-1表示没有元素）
    
    return s;  // 返回创建成功的栈指针
}

/**
 * 销毁栈，释放所有相关内存
 */
stack_result_t sqstack_destroy(sqstack_t* s) {
    // 检查输入参数的有效性
    if (s == NULL) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    // 先释放数据数组内存
    if (s->data != NULL) {
        free(s->data);
        s->data = NULL;  // 重要：设置为NULL，防止悬挂指针
                        // 悬挂指针是指向已释放内存的指针，使用它会导致未定义行为
    }
    
    // 再释放栈结构体内存
    free(s);
    
    return STACK_SUCCESS;
}

/**
 * 向栈顶压入一个元素
 */
stack_result_t sqstack_push(sqstack_t* s, data_t value) {
    // 第一步：检查栈的有效性
    if (!is_valid_stack(s)) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    // 第二步：检查栈是否已满
    // top >= maxlen-1 表示栈已满（因为索引从0开始）
    if (s->top >= s->maxlen - 1) {
        return STACK_ERROR_STACK_FULL;
    }
    
    // 第三步：执行压栈操作
    // ++s->top: 先将栈顶索引加1，再使用新值作为数组索引
    // 这样确保新元素放在正确的位置
    s->data[++s->top] = value;
    
    return STACK_SUCCESS;
}

/**
 * 从栈顶弹出一个元素（删除并返回栈顶元素）
 */
stack_result_t sqstack_pop(sqstack_t* s, data_t* value) {
    // 第一步：检查栈的有效性
    if (!is_valid_stack(s)) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    // 第二步：检查输出参数的有效性
    // value是用来接收弹出值的指针，不能为NULL
    if (value == NULL) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    // 第三步：检查栈是否为空
    if (s->top == -1) {
        return STACK_ERROR_STACK_EMPTY;
    }
    
    // 第四步：执行弹栈操作
    // s->top--: 后置递减，先使用当前top值作为索引，然后top减1
    // *value: 通过指针将弹出的值写入调用者提供的变量
    *value = s->data[s->top--];
    
    return STACK_SUCCESS;
}

/**
 * 查看栈顶元素但不删除
 */
stack_result_t sqstack_top(sqstack_t* s, data_t* value) {
    // 第一步：检查栈的有效性
    if (!is_valid_stack(s)) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    // 第二步：检查输出参数的有效性
    if (value == NULL) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    // 第三步：检查栈是否为空
    if (s->top == -1) {
        return STACK_ERROR_STACK_EMPTY;
    }
    
    // 第四步：获取栈顶元素值
    // 注意：这里只是读取s->data[s->top]，不修改top值
    // 所以栈的大小和状态都不会改变
    *value = s->data[s->top];
    
    return STACK_SUCCESS;
}

/**
 * 清空栈（逻辑清空，不释放内存）
 */
stack_result_t sqstack_clear(sqstack_t* s) {
    // 检查栈的有效性
    if (!is_valid_stack(s)) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    // 逻辑清空：只需将top重置为-1
    // 数据数组的内容不需要清除，因为它们不会被访问
    // 这比逐个删除元素或用memset清零效率高得多
    s->top = -1;
    
    return STACK_SUCCESS;
}

// ============== 栈的查询函数实现 ==============

/**
 * 检查栈是否为空
 */
bool sqstack_is_empty(const sqstack_t* s) {
    // 如果栈无效，我们认为它是"空"的（无法进行操作）
    if (!is_valid_stack(s)) {
        return true;
    }
    
    // top == -1 是空栈的标志
    return (s->top == -1);
}

/**
 * 检查栈是否已满
 */
bool sqstack_is_full(const sqstack_t* s) {
    // 如果栈无效，我们认为它是"未满"的（无法进行push操作）
    if (!is_valid_stack(s)) {
        return false;
    }
    
    // top == maxlen-1 表示栈已满
    // 因为数组索引范围是 0 到 maxlen-1
    return (s->top == s->maxlen - 1);
}

/**
 * 获取栈中当前元素个数
 */
int sqstack_size(const sqstack_t* s) {
    // 检查栈的有效性
    if (!is_valid_stack(s)) {
        return -1;  // 返回-1表示错误
    }
    
    // 栈的大小 = top索引 + 1
    // 因为top是从-1开始的，所以元素个数是top+1
    // 例如：top=-1时有0个元素，top=0时有1个元素
    return s->top + 1;
}

/**
 * 获取栈的最大容量
 */
int sqstack_capacity(const sqstack_t* s) {
    // 检查栈的有效性
    if (!is_valid_stack(s)) {
        return -1;  // 返回-1表示错误
    }
    
    // 直接返回maxlen字段
    return s->maxlen;
}

// ============== 高级功能函数实现 ==============

/**
 * 动态调整栈的容量
 */
stack_result_t sqstack_resize(sqstack_t* s, int new_capacity) {
    // 第一步：检查栈的有效性
    if (!is_valid_stack(s)) {
        return STACK_ERROR_NULL_POINTER;
    }
    
    // 第二步：检查新容量的有效性
    if (new_capacity <= 0) {
        return STACK_ERROR_INVALID_SIZE;
    }
    
    // 第三步：防止数据丢失
    // 如果新容量小于等于当前元素数量，拒绝调整
    // 因为这会导致栈顶的一些元素丢失
    if (new_capacity <= s->top) {
        return STACK_ERROR_INVALID_SIZE;
    }
    
    // 第四步：使用realloc调整内存大小
    // realloc的智能行为：
    // 1. 如果可能，在原地扩展内存（性能最佳）
    // 2. 如果不行，分配新内存并自动复制数据，释放旧内存
    // 3. 如果失败，返回NULL，但原内存保持不变
    data_t* new_data = (data_t*)realloc(s->data, sizeof(data_t) * new_capacity);
    
    // 第五步：检查realloc是否成功
    if (new_data == NULL) {
        // 失败时原内存仍然有效，栈的状态没有改变
        return STACK_ERROR_MEMORY_ALLOCATION;
    }
    
    // 第六步：更新栈的属性
    // 只有在realloc成功后才更新指针，确保安全性
    s->data = new_data;
    s->maxlen = new_capacity;
    
    return STACK_SUCCESS;
}

// ============== 辅助函数实现 ==============

/**
 * 打印栈操作的错误信息
 * 这是一个辅助函数，帮助用户理解操作结果
 */
void print_stack_error(stack_result_t result) {
    switch (result) {
        case STACK_SUCCESS:
            printf("Operation successful\n");
            break;
        case STACK_ERROR_NULL_POINTER:
            printf("Error: Null pointer\n");
            break;
        case STACK_ERROR_MEMORY_ALLOCATION:
            printf("Error: Memory allocation failed\n");
            break;
        case STACK_ERROR_STACK_FULL:
            printf("Error: Stack is full\n");
            break;
        case STACK_ERROR_STACK_EMPTY:
            printf("Error: Stack is empty\n");
            break;
        case STACK_ERROR_INVALID_SIZE:
            printf("Error: Invalid size parameter\n");
            break;
        default:
            printf("Error: Unknown error\n");
            break;
    }
}

// ============== 测试函数实现 ==============

/**
 * 栈功能的基本测试函数
 * 演示了栈的创建、使用和销毁的完整流程
 */
void test_stack() {
    printf("=== Stack Test ===\n");
    
    // 第一步：创建栈
    sqstack_t* stack = sqstack_create(5);
    if (stack == NULL) {
        printf("Failed to create stack\n");
        return;
    }
    
    // 第二步：测试压栈操作
    printf("\n--- Testing Push Operations ---\n");
    for (int i = 1; i <= 3; i++) {
        stack_result_t result = sqstack_push(stack, i * 10);
        printf("Push %d: ", i * 10);
        print_stack_error(result);
    }
    
    // 第三步：查看栈的状态
    printf("\n--- Stack Status ---\n");
    printf("Stack size: %d, capacity: %d\n", sqstack_size(stack), sqstack_capacity(stack));
    printf("Is empty: %s, Is full: %s\n", 
           sqstack_is_empty(stack) ? "true" : "false",
           sqstack_is_full(stack) ? "true" : "false");
    
    // 第四步：测试查看栈顶操作
    printf("\n--- Testing Top Operation ---\n");
    data_t value;
    stack_result_t result = sqstack_top(stack, &value);
    if (result == STACK_SUCCESS) {
        printf("Top element: %d\n", value);
    }
    
    // 第五步：测试弹栈操作
    printf("\n--- Testing Pop Operations ---\n");
    while (!sqstack_is_empty(stack)) {
        result = sqstack_pop(stack, &value);
        if (result == STACK_SUCCESS) {
            printf("Popped: %d\n", value);
        }
    }
    
    // 第六步：清理资源
    printf("\n--- Cleanup ---\n");
    sqstack_destroy(stack);
    printf("Stack destroyed\n");
}
