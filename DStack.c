#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "DStack.h"

DStack  dstack_create(){
    struct DStack stack = {0, 0, NULL};
    return stack;
}

int dstack_push(int item, DStack *stack){
    if(__dstack_buffer_realloc_up(stack)){
        stack->head = stack->buffer_size - 1;
        stack->buffer[stack->head] = item;
        return 1;
    }
    return -1;
}

int dstack_pop(DStack *stack){
    if(!dstack_isempty(stack)){
        int pop_item = stack->buffer[stack->head];
        if(__dstack_buffer_realloc_down(stack)){
            stack->head  = stack->buffer_size == 0 ? 0 : stack->buffer_size - 1;
            return pop_item;
        }
    }
    return -1;
}

int __dstack_buffer_realloc_up(DStack *stack){
    int new_buffer_size = stack->buffer_size + 1;
    if(stack->buffer_size == 0){
        errno = 0;
        stack->buffer = calloc(1, sizeof(int) * new_buffer_size );
        if(!stack->buffer){
            perror("__dstack_buffer_realloc_up calloc(): ");
            exit(-1);
        }
        stack->buffer_size = new_buffer_size;
        return 1;
    }else{
        errno = 0;
        stack->buffer = realloc(stack->buffer, sizeof(int) * new_buffer_size);
        if(!stack->buffer){
            perror("__dstack_buffer_realloc_up realloc(): ");
            exit(-1);
        }
        stack->buffer_size = new_buffer_size;
        return 1;
    }
}

int __dstack_buffer_realloc_down(DStack *stack){
    int new_buffer_size = stack->buffer_size - 1;
    if(new_buffer_size == 0){
        free(stack->buffer);
        stack->buffer_size = new_buffer_size;
        return 1;
    }else{
        errno = 0;
        stack->buffer = realloc(stack->buffer, sizeof(int) * new_buffer_size);
        if(!stack->buffer){
            perror("__dstack_buffer_realloc_down realloc(): ");
            exit(-1);
        }
        stack->buffer_size = new_buffer_size;
        return 1;
    }
}

int dstack_isempty(struct DStack *stack){
    return !stack->buffer_size;
}

void dstack_debug(DStack *stack){
    printf("\nDStack DEBUG___________________________________\n");
    printf("Head: %d\nSize: %d\nBuffer: ", stack->head, stack->buffer_size);
    for(int i = 0; i < stack->buffer_size; i++){
        printf("%d", stack->buffer[i]);
    }
    printf("\n");
}

