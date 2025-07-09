#include <stdio.h>
#include"sqlist.h"
#include <stdlib.h>
int main(int argc,char* argv[]){
    sqlink L;
    L = list_create();
    list_insert(L,1,0);
    list_insert(L,2,0);
    list_insert(L,3,0);
    list_insert(L,4,0);
    list_insert(L,5,0);
    list_show(L);
    list_clear(L);
    free(L);
    return 0;

}





