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

// ============== 辅助函数声明 ==============

/**
 * 打印栈操作的错误信息
 * 这是一个辅助函数，帮助用户理解操作结果
 * @param result 要打印的状态码
 */
void print_stack_error(stack_result_t result);

/**
 * 栈功能的基本测试函数
 * 演示了栈的创建、使用和销毁的完整流程
 */
void test_stack(void);

#endif
