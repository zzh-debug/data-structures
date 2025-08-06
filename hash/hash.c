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
    if((p = (linklist)malloc(sizeof(listnode))) == NULL) {
        printf("malloc listnode failed\n");
        return -1;
    }
    p->key = key;
    p->value = key % N;
    p->next = NULL;
    q = &(HT->data[key % N]);
    while(q->next != NULL && q->next->key < p->key) {
        q = q->next;
    }
    p->next = q->next;
    q->next = p;

    return 0;
}


linklist hash_search(hash* HT,datatype key) {
    if (HT == NULL) {
        printf("HT is NULL\n");
        return NULL;
    }
    linklist p;

    p = &(HT->data[key % N]);
    while (p->next && p->next->key != key) {
        p = p->next;
    }
    if (p->next == NULL) {
        return NULL;
    } else {
        return p->next;
    }
}
