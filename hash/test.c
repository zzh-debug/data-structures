#include <stdio.h>
#include <stdlib.h>

int main(int argc,const char* argv[]) {
    hash* HT;
    int data[] = {23, 34, 14, 38, 46, 16, 68, 15, 7, 31, 26};
    int i;
    int key;
    linklist r;
    HT = hash_create();
    if (HT == NULL) {
        return -1;
    }
    for (i, i<sizeof(data)/sizeof(int)) {
        hash_insert(HT,data[i]);
    }
    printf("input: ");
    scanf("%d",&key);
    r = hash_search(HT,key);
    if (r == NULL) {
        printf("not found\n");
    }else {
        printf("found: %d %d\n",key, r->key);
    }
    return 0;
}

