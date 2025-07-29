#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main() {
    bitree* root;
    
    printf("=== 二叉树测试程序 ===\n");
    printf("请按前序输入二叉树，用 # 表示空节点\n");
    printf("示例输入:\n");
    printf("  简单树: AB##C##\n");
    printf("  复杂树: ABC##DE#G##F###\n");
    printf("\n请输入: ");
    
    // 创建二叉树
    root = tree_create();
    
    if (root == NULL) {
        printf("树为空或创建失败\n");
        return 1;
    }
    
    printf("\n=== 遍历结果 ===\n");
    
    // 前序遍历
    printf("前序遍历: ");
    preorder(root);
    printf("\n");
    
    // 中序遍历  
    printf("中序遍历: ");
    inorder(root);
    printf("\n");
    
    // 后序遍历
    printf("后序遍历: ");
    postorder(root);
    printf("\n");
    
    // 释放内存
    tree_destroy(root);
    printf("\n内存已释放，程序结束\n");
    
    return 0;
}
