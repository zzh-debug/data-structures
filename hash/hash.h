#ifndef HASH_H
#define HASH_H
#define N 15
typedef int datatype;
typedef struct node {
    datatype key;
    datatype value;
    struct node* next;
}listnode,*linklist;
/* hash 结构体包含一个数组 data，这个数组有 N(15) 个 listnode 元素
 hash结构体的内存布局：
┌─────────────────────────────────────────┐
│ hash                                    │
│ ┌─────────────────────────────────────┐ │
│ │ data[0]  {key, value, next}         │ │  <- 哈希桶0的头节点
│ │ data[1]  {key, value, next}         │ │  <- 哈希桶1的头节点  
│ │ data[2]  {key, value, next}         │ │  <- 哈希桶2的头节点
│ │ ...                                 │ │
│ │ data[14] {key, value, next}         │ │  <- 哈希桶14的头节点
│ └─────────────────────────────────────┘ │
└─────────────────────────────────────────┘
*/
typedef struct {
    listnode data[N];
}hash;

hash* hash_create();
int hash_insert(hash* HT,datatype key);
linklist* hash_search(hash* HT,datatype key);

#endif
