#include <stdio.h>
#include <stdlib.h>
#include "sqstack.h"

int main(int argc[];const char* argv[]){
    sqstack*s;
    s = stack_create(100);
    if (s == NULL) {
        return -1;
    }
    return 0;
}
