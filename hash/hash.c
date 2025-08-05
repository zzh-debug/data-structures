#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

hash* hash_create() {
    hash* HT;
    HT = (hash*)malloc(sizeof(hash));
    if (HT == NULL) {
        printf("malloc hash failed!\n");
        return NULL;
    }
    memset(HT,0,sizeof(hash));
    return HT;
}

int hash_insert(hash* HT,datatype key) {
    if (HT == NULL) {
        printf("HT is NULL!\n");
        return -1;
    }
    linklist p;
    linklist q;
    if(p = (linklist*)malloc(sizeof(listnode)) == NULL) {
        printf("malloc listnode failed\n");
        return -1;
    }
    p->key = key;
    p->value = key % N;
    p->next = NULL;
    q = &(HT->data[key % N]);
    if (q->next == NULL) {
        q->next = p;
    }
}


linklist* hash_search(hash* HT,datatype key) {

}
