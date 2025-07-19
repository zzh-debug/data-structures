/**
 * test.c - 栈功能测试文件
 * 
 * 这个文件包含了对栈实现的全面测试，包括：
 * 1. 基本功能测试（创建、压栈、弹栈等）
 * 2. 边界条件测试（空栈、满栈等）
 * 3. 错误处理测试（无效参数等）
 * 4. 性能测试（大量数据操作）
 * 5. 内存管理测试（扩容等）
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "sqstack.h"  // 包含栈的实现

// ============== 测试辅助宏定义 ==============

// 测试计数器
static int test_count = 0;
static int pass_count = 0;

// 测试断言宏，用于验证结果
#define TEST_ASSERT(condition, description) do { \
    test_count++; \
    if (condition) { \
        printf("✓ Test %d PASSED: %s\n", test_count, description); \
        pass_count++; \
    } else { \
        printf("✗ Test %d FAILED: %s\n", test_count, description); \
    } \
} while(0)

// 打印测试分隔线（修复语法错误）
#define PRINT_SEPARATOR(title) do { \
    printf("\n"); \
    for(int i = 0; i < 60; i++) printf("="); \
    printf("\n  %s\n", title); \
    for(int i = 0; i < 60; i++) printf("="); \
    printf("\n"); \
} while(0)

// ============== 测试辅助函数 ==============

/**
 * 打印栈的详细状态信息
 * @param s 栈指针
 * @param title 状态标题
 */
void print_stack_status(sqstack_t* s, const char* title) {
    printf("\n--- %s ---\n", title);
    
    if (s == NULL) {
        printf("栈指针为 NULL\n");
        return;
    }
    
    printf("容量: %d\n", sqstack_capacity(s));
    printf("大小: %d\n", sqstack_size(s));
    printf("是否为空: %s\n", sqstack_is_empty(s) ? "是" : "否");
    printf("是否已满: %s\n", sqstack_is_full(s) ? "是" : "否");
}

/**
 * 安全的栈操作包装函数，带错误检查
 */
bool safe_push_and_check(sqstack_t* s, data_t value, stack_result_t expected_result) {
    stack_result_t result = sqstack_push(s, value);
    printf("Push %d: ", value);
    print_stack_error(result);
    return (result == expected_result);
}

bool safe_pop_and_check(sqstack_t* s, data_t* value, stack_result_t expected_result) {
    stack_result_t result = sqstack_pop(s, value);
    if (result == STACK_SUCCESS) {
        printf("Pop 成功: %d\n", *value);
    } else {
        printf("Pop 失败: ");
        print_stack_error(result);
    }
    return (result == expected_result);
}

// ============== 具体测试函数 ==============

/**
 * 测试栈的创建和销毁功能
 */
void test_stack_creation_and_destruction() {
    PRINT_SEPARATOR("测试栈的创建和销毁");
    
    // 测试1：正常创建
    sqstack_t* stack1 = sqstack_create(10);
    TEST_ASSERT(stack1 != NULL, "正常参数创建栈");
    TEST_ASSERT(sqstack_capacity(stack1) == 10, "栈容量设置正确");
    TEST_ASSERT(sqstack_size(stack1) == 0, "新栈大小为0");
    TEST_ASSERT(sqstack_is_empty(stack1) == true, "新栈为空");
    TEST_ASSERT(sqstack_is_full(stack1) == false, "新栈未满");
    
    // 测试2：无效参数自动修正
    sqstack_t* stack2 = sqstack_create(0);
    TEST_ASSERT(stack2 != NULL, "无效参数(0)自动修正创建栈");
    TEST_ASSERT(sqstack_capacity(stack2) == 10, "无效参数自动使用默认容量");
    
    sqstack_t* stack3 = sqstack_create(-5);
    TEST_ASSERT(stack3 != NULL, "无效参数(-5)自动修正创建栈");
    TEST_ASSERT(sqstack_capacity(stack3) == 10, "负数参数自动使用默认容量");
    
    // 测试3：销毁栈
    stack_result_t result1 = sqstack_destroy(stack1);
    TEST_ASSERT(result1 == STACK_SUCCESS, "正常销毁栈");
    
    stack_result_t result2 = sqstack_destroy(NULL);
    TEST_ASSERT(result2 == STACK_ERROR_NULL_POINTER, "销毁NULL指针返回错误");
    
    // 清理
    sqstack_destroy(stack2);
    sqstack_destroy(stack3);
}

/**
 * 测试基本的压栈和弹栈操作
 */
void test_basic_push_pop_operations() {
    PRINT_SEPARATOR("测试基本的压栈和弹栈操作");
    
    sqstack_t* stack = sqstack_create(5);
    TEST_ASSERT(stack != NULL, "创建测试栈");
    
    // 测试压栈操作
    printf("\n--- 测试压栈操作 ---\n");
    for (int i = 1; i <= 3; i++) {
        stack_result_t result = sqstack_push(stack, i * 100);
        TEST_ASSERT(result == STACK_SUCCESS, "压入元素成功");
        TEST_ASSERT(sqstack_size(stack) == i, "栈大小正确增长");
    }
    
    print_stack_status(stack, "压入3个元素后的状态");
    
    // 测试查看栈顶操作
    printf("\n--- 测试查看栈顶操作 ---\n");
    data_t top_value;
    stack_result_t result = sqstack_top(stack, &top_value);
    TEST_ASSERT(result == STACK_SUCCESS, "查看栈顶成功");
    TEST_ASSERT(top_value == 300, "栈顶值正确");
    TEST_ASSERT(sqstack_size(stack) == 3, "查看栈顶后大小不变");
    
    // 测试弹栈操作
    printf("\n--- 测试弹栈操作 ---\n");
    data_t popped_values[3];
    int expected_values[] = {300, 200, 100};  // 期望的弹出顺序
    
    for (int i = 0; i < 3; i++) {
        result = sqstack_pop(stack, &popped_values[i]);
        TEST_ASSERT(result == STACK_SUCCESS, "弹栈操作成功");
        TEST_ASSERT(popped_values[i] == expected_values[i], "弹出值正确");
        TEST_ASSERT(sqstack_size(stack) == (3 - i - 1), "栈大小正确减少");
    }
    
    TEST_ASSERT(sqstack_is_empty(stack) == true, "弹出所有元素后栈为空");
    
    sqstack_destroy(stack);
}

/**
 * 测试边界条件和错误处理
 */
void test_boundary_and_error_conditions() {
    PRINT_SEPARATOR("测试边界条件和错误处理");
    
    sqstack_t* stack = sqstack_create(3);  // 创建小容量栈用于测试
    
    // 测试1：空栈操作
    printf("\n--- 测试空栈操作 ---\n");
    data_t value;
    stack_result_t result;
    
    result = sqstack_pop(stack, &value);
    TEST_ASSERT(result == STACK_ERROR_STACK_EMPTY, "空栈弹出返回错误");
    
    result = sqstack_top(stack, &value);
    TEST_ASSERT(result == STACK_ERROR_STACK_EMPTY, "空栈查看栈顶返回错误");
    
    // 测试2：满栈操作
    printf("\n--- 测试满栈操作 ---\n");
    // 先填满栈
    for (int i = 0; i < 3; i++) {
        result = sqstack_push(stack, (i + 1) * 10);
        TEST_ASSERT(result == STACK_SUCCESS, "正常压入元素");
    }
    
    TEST_ASSERT(sqstack_is_full(stack) == true, "栈已满状态检查");
    
    // 尝试再压入一个元素
    result = sqstack_push(stack, 999);
    TEST_ASSERT(result == STACK_ERROR_STACK_FULL, "满栈压入返回错误");
    
    // 测试3：NULL指针操作
    printf("\n--- 测试NULL指针操作 ---\n");
    result = sqstack_push(NULL, 100);
    TEST_ASSERT(result == STACK_ERROR_NULL_POINTER, "NULL栈指针压入返回错误");
    
    result = sqstack_pop(NULL, &value);
    TEST_ASSERT(result == STACK_ERROR_NULL_POINTER, "NULL栈指针弹出返回错误");
    
    result = sqstack_pop(stack, NULL);
    TEST_ASSERT(result == STACK_ERROR_NULL_POINTER, "NULL输出参数弹出返回错误");
    
    result = sqstack_top(stack, NULL);
    TEST_ASSERT(result == STACK_ERROR_NULL_POINTER, "NULL输出参数查看栈顶返回错误");
    
    sqstack_destroy(stack);
}

/**
 * 测试栈的清空功能
 */
void test_stack_clear_operation() {
    PRINT_SEPARATOR("测试栈的清空功能");
    
    sqstack_t* stack = sqstack_create(10);
    
    // 先添加一些元素
    printf("\n--- 添加测试数据 ---\n");
    for (int i = 1; i <= 5; i++) {
        sqstack_push(stack, i * 50);
    }
    
    print_stack_status(stack, "清空前的状态");
    TEST_ASSERT(sqstack_size(stack) == 5, "清空前栈有5个元素");
    TEST_ASSERT(sqstack_is_empty(stack) == false, "清空前栈非空");
    
    // 执行清空操作
    printf("\n--- 执行清空操作 ---\n");
    stack_result_t result = sqstack_clear(stack);
    TEST_ASSERT(result == STACK_SUCCESS, "清空操作成功");
    
    print_stack_status(stack, "清空后的状态");
    TEST_ASSERT(sqstack_size(stack) == 0, "清空后栈大小为0");
    TEST_ASSERT(sqstack_is_empty(stack) == true, "清空后栈为空");
    TEST_ASSERT(sqstack_capacity(stack) == 10, "清空后容量不变");
    
    // 测试清空后的正常操作
    printf("\n--- 清空后重新使用 ---\n");
    result = sqstack_push(stack, 999);
    TEST_ASSERT(result == STACK_SUCCESS, "清空后可以正常压入");
    TEST_ASSERT(sqstack_size(stack) == 1, "清空后重新压入大小正确");
    
    sqstack_destroy(stack);
}

/**
 * 测试栈的动态扩容功能
 */
void test_stack_resize_operation() {
    PRINT_SEPARATOR("测试栈的动态扩容功能");
    
    sqstack_t* stack = sqstack_create(3);
    
    // 添加一些元素
    printf("\n--- 添加初始数据 ---\n");
    for (int i = 1; i <= 2; i++) {
        sqstack_push(stack, i * 100);
    }
    
    print_stack_status(stack, "扩容前状态");
    
    // 测试1：正常扩容
    printf("\n--- 测试正常扩容 ---\n");
    stack_result_t result = sqstack_resize(stack, 8);
    TEST_ASSERT(result == STACK_SUCCESS, "扩容操作成功");
    TEST_ASSERT(sqstack_capacity(stack) == 8, "扩容后容量正确");
    TEST_ASSERT(sqstack_size(stack) == 2, "扩容后大小不变");
    
    // 验证数据完整性
    data_t value;
    sqstack_top(stack, &value);
    TEST_ASSERT(value == 200, "扩容后数据完整性保持");
    
    print_stack_status(stack, "扩容后状态");
    
    // 测试扩容后的正常操作
    printf("\n--- 测试扩容后操作 ---\n");
    for (int i = 3; i <= 6; i++) {
        result = sqstack_push(stack, i * 100);
        TEST_ASSERT(result == STACK_SUCCESS, "扩容后可以压入更多元素");
    }
    
    TEST_ASSERT(sqstack_size(stack) == 6, "扩容后压入多个元素大小正确");
    
    // 测试2：无效扩容参数
    printf("\n--- 测试无效扩容参数 ---\n");
    result = sqstack_resize(stack, 0);
    TEST_ASSERT(result == STACK_ERROR_INVALID_SIZE, "扩容到0返回错误");
    
    result = sqstack_resize(stack, -5);
    TEST_ASSERT(result == STACK_ERROR_INVALID_SIZE, "扩容到负数返回错误");
    
    result = sqstack_resize(stack, 3);  // 小于当前元素数量
    TEST_ASSERT(result == STACK_ERROR_INVALID_SIZE, "扩容到小于当前大小返回错误");
    
    // 测试3：NULL指针扩容
    result = sqstack_resize(NULL, 10);
    TEST_ASSERT(result == STACK_ERROR_NULL_POINTER, "NULL栈指针扩容返回错误");
    
    sqstack_destroy(stack);
}

/**
 * 测试栈的性能（大量数据操作）
 */
void test_stack_performance() {
    PRINT_SEPARATOR("测试栈的性能（大量数据操作）");
    
    const int test_size = 10000;  // 测试数据量
    sqstack_t* stack = sqstack_create(test_size);
    
    printf("测试数据量: %d 个元素\n", test_size);
    
    // 测试大量压栈操作的性能
    printf("\n--- 测试大量压栈操作 ---\n");
    clock_t start_time = clock();
    
    int success_count = 0;
    for (int i = 0; i < test_size; i++) {
        if (sqstack_push(stack, i) == STACK_SUCCESS) {
            success_count++;
        }
    }
    
    clock_t end_time = clock();
    double push_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    
    TEST_ASSERT(success_count == test_size, "大量压栈操作全部成功");
    TEST_ASSERT(sqstack_size(stack) == test_size, "大量压栈后大小正确");
    printf("压栈 %d 个元素耗时: %.4f 秒\n", test_size, push_time);
    
    // 测试大量弹栈操作的性能
    printf("\n--- 测试大量弹栈操作 ---\n");
    start_time = clock();
    
    data_t value;
    success_count = 0;
    for (int i = 0; i < test_size; i++) {
        if (sqstack_pop(stack, &value) == STACK_SUCCESS) {
            success_count++;
            // 验证弹出顺序正确（LIFO）
            if (value != (test_size - 1 - i)) {
                printf("弹出顺序错误: 期望 %d, 实际 %d\n", test_size - 1 - i, value);
                break;
            }
        }
    }
    
    end_time = clock();
    double pop_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    
    TEST_ASSERT(success_count == test_size, "大量弹栈操作全部成功");
    TEST_ASSERT(sqstack_is_empty(stack) == true, "大量弹栈后栈为空");
    printf("弹栈 %d 个元素耗时: %.4f 秒\n", test_size, pop_time);
    
    sqstack_destroy(stack);
}

/**
 * 综合功能测试（模拟实际使用场景）
 */
void test_comprehensive_scenario() {
    PRINT_SEPARATOR("综合功能测试（模拟实际使用场景）");
    
    printf("\n模拟场景：使用栈来检查括号匹配\n");
    
    sqstack_t* stack = sqstack_create(50);
    const char* test_expression = "((()))(()";  // 不匹配的括号表达式
    
    printf("测试表达式: %s\n", test_expression);
    
    // 处理表达式
    int i = 0;
    bool is_valid = true;
    
    while (test_expression[i] != '\0' && is_valid) {
        char ch = test_expression[i];
        
        if (ch == '(') {
            // 遇到左括号，压栈
            stack_result_t result = sqstack_push(stack, 1);
            if (result != STACK_SUCCESS) {
                printf("压栈失败\n");
                is_valid = false;
            }
        } else if (ch == ')') {
            // 遇到右括号，弹栈
            data_t value;
            stack_result_t result = sqstack_pop(stack, &value);
            if (result != STACK_SUCCESS) {
                printf("在位置 %d 发现多余的右括号\n", i);
                is_valid = false;
            }
        }
        i++;
    }
    
    // 检查是否还有未匹配的左括号
    if (is_valid && !sqstack_is_empty(stack)) {
        printf("发现 %d 个未匹配的左括号\n", sqstack_size(stack));
        is_valid = false;
    }
    
    if (is_valid) {
        printf("括号匹配正确\n");
    } else {
        printf("括号匹配错误\n");
    }
    
    TEST_ASSERT(!is_valid, "正确检测出括号不匹配");
    
    sqstack_destroy(stack);
}

/**
 * 打印测试总结
 */
void print_test_summary() {
    PRINT_SEPARATOR("测试总结");
    
    printf("总测试数: %d\n", test_count);
    printf("通过测试: %d\n", pass_count);
    printf("失败测试: %d\n", test_count - pass_count);
    printf("通过率: %.1f%%\n", (float)pass_count / test_count * 100);
    
    if (pass_count == test_count) {
        printf("\n🎉 所有测试通过！栈实现正确！\n");
    } else {
        printf("\n❌ 有测试失败，请检查栈实现！\n");
    }
}

// ============== 主函数 ==============

/**
 * 主测试函数
 * 依次执行所有测试用例
 */
int main() {
    printf("🧪 栈数据结构测试程序\n");
    printf("测试开始时间: %s", ctime(&(time_t){time(NULL)}));
    
    // 执行所有测试
    test_stack_creation_and_destruction();
    test_basic_push_pop_operations();
    test_boundary_and_error_conditions();
    test_stack_clear_operation();
    test_stack_resize_operation();
    test_stack_performance();
    test_comprehensive_scenario();
    
    // 打印总结
    print_test_summary();
    
    return (pass_count == test_count) ? 0 : 1;  // 所有测试通过返回0，否则返回1
}
