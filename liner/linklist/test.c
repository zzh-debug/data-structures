#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

int main(int argc,int* argv[]){
    listlink head = NULL;
    head = list_create();
    list_tail_insert(head,10);
    list_tail_insert(head,20);
    list_tail_insert(head,30);
    list_head_insert(head,1);
    list_head_insert(head,2);
    list_head_insert(head,3);
    list_pos_insert(head,3,100);
    printf("length = %d\n",list_length(head));
    list_show(head);
    list_pos_delet(head,1);
    printf("length = %d\n",list_length(head));
    list_show(head);
    list_reverse(head);
    list_show(head);
    list_free(head);
    return 0;
}
