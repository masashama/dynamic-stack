#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "DStack.h"


int main(){
    DStack dstack = dstack_create();
    for(int i = 0; i < 50; i++){
        dstack_push(i, &dstack);
    }
    dstack_debug(&dstack);
    while(!dstack_isempty(&dstack)){
        printf("%d", dstack_pop(&dstack));
    }
    dstack_debug(&dstack);
    printf("\n");
    return 0;
}













