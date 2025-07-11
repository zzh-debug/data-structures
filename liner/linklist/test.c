#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

int main(int argc,int* argv[]){
    listlink head = NULL;
    head = list_create();
    list_tail_insert(head,10);
    list_tail_insert(head,20);
    list_tail_insert(head,30);
    list_tail_insert(head,40);
    list_tail_insert(head,50);
    list_tail_insert(head,60);
    list_tail_insert(head,70);
    list_show(head);
    list_free(head);
    return 0;
}
