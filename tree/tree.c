#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// 递归创建二叉树（前序输入）
// 输入格式：用 '#' 表示空节点
// 例如：ABC##DE#G##F### 表示一个二叉树
bitree* tree_create() {
    char ch;
    bitree* r;
    
    scanf("%c", &ch);
    
    // 如果输入是 '#'，表示空节点
    if (ch == '#') {
        return NULL;
    }
    
    // 为新节点分配内存
    if ((r = (bitree*)malloc(sizeof(bitree))) == NULL) {
        printf("malloc failed\n");
        return NULL;
    }
    
    // 设置节点数据
    r->data = ch;
    
    // 递归创建左子树
    r->left = tree_create();
    
    // 递归创建右子树
    r->right = tree_create();
    
    return r;
}

// 前序遍历：根 -> 左 -> 右
void preorder(bitree* r) {
    if (r != NULL) {
        printf("%c ", r->data);    // 访问根节点
        preorder(r->left);         // 遍历左子树
        preorder(r->right);        // 遍历右子树
    }
}

// 中序遍历：左 -> 根 -> 右
void inorder(bitree* r) {
    if (r != NULL) {
        inorder(r->left);          // 遍历左子树
        printf("%c ", r->data);    // 访问根节点
        inorder(r->right);         // 遍历右子树
    }
}

// 后序遍历：左 -> 右 -> 根
void postorder(bitree* r) {
    if (r != NULL) {
        postorder(r->left);        // 遍历左子树
        postorder(r->right);       // 遍历右子树
        printf("%c ", r->data);    // 访问根节点
    }
}

// 辅助函数：释放树的内存
void tree_destroy(bitree* r) {
    if (r != NULL) {
        tree_destroy(r->left);
        tree_destroy(r->right);
        free(r);
    }
}
