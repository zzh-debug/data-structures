#include <stdio.h>
#include "linkstack.h"

void print_separator(const char* test_name) {
    printf("\n=== %s ===\n", test_name);
}

int main() {
    printf("链栈功能测试程序\n");
    
    // 测试1: 创建栈
    print_separator("测试1: 创建栈");
    linkstack stack = stack_create();
    if (stack != NULL) {
        printf("✓ 栈创建成功\n");
    } else {
        printf("✗ 栈创建失败\n");
        return -1;
    }
    
    // 测试2: 检查空栈
    print_separator("测试2: 检查空栈");
    if (stack_empty(stack) == 1) {
        printf("✓ 空栈检测正确\n");
    } else {
        printf("✗ 空栈检测错误\n");
    }
    
    // 测试3: 空栈出栈和查看栈顶（应该有错误提示）
    print_separator("测试3: 空栈操作");
    printf("尝试对空栈进行出栈操作:\n");
    data_t empty_pop = stack_pop(stack);
    printf("出栈结果: %d\n", empty_pop);
    
    printf("尝试查看空栈栈顶:\n");
    data_t empty_top = stack_top(stack);
    printf("栈顶结果: %d\n", empty_top);
    
    // 测试4: 入栈操作
    print_separator("测试4: 入栈操作");
    printf("依次入栈: 10, 20, 30, 40, 50\n");
    
    int values[] = {10, 20, 30, 40, 50};
    int size = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < size; i++) {
        if (stack_push(stack, values[i]) == 0) {
            printf("✓ 成功入栈: %d\n", values[i]);
        } else {
            printf("✗ 入栈失败: %d\n", values[i]);
        }
    }
    
    // 测试5: 检查非空栈
    print_separator("测试5: 检查非空栈");
    if (stack_empty(stack) == 0) {
        printf("✓ 非空栈检测正确\n");
    } else {
        printf("✗ 非空栈检测错误\n");
    }
    
    // 测试6: 查看栈顶元素
    print_separator("测试6: 查看栈顶元素");
    data_t top_value = stack_top(stack);
    printf("当前栈顶元素: %d (应该是50)\n", top_value);
    if (top_value == 50) {
        printf("✓ 栈顶元素正确\n");
    } else {
        printf("✗ 栈顶元素错误\n");
    }
    
    // 测试7: 出栈操作
    print_separator("测试7: 出栈操作");
    printf("逐个出栈:\n");
    
    while (!stack_empty(stack)) {
        data_t popped = stack_pop(stack);
        printf("出栈元素: %d\n", popped);
    }
    
    // 测试8: 再次检查空栈
    print_separator("测试8: 再次检查空栈");
    if (stack_empty(stack) == 1) {
        printf("✓ 出栈后空栈检测正确\n");
    } else {
        printf("✗ 出栈后空栈检测错误\n");
    }
    
    // 测试9: 混合操作
    print_separator("测试9: 混合操作");
    printf("入栈100, 200\n");
    stack_push(stack, 100);
    stack_push(stack, 200);
    
    printf("栈顶: %d\n", stack_top(stack));
    printf("出栈: %d\n", stack_pop(stack));
    printf("栈顶: %d\n", stack_top(stack));
    
    printf("入栈300\n");
    stack_push(stack, 300);
    printf("栈顶: %d\n", stack_top(stack));
    
    // 测试10: 释放栈
    print_separator("测试10: 释放栈");
    if (stack_free(stack) == 0) {
        printf("✓ 栈释放成功\n");
    } else {
        printf("✗ 栈释放失败\n");
    }
    
    printf("\n所有测试完成！\n");
    return 0;
}
