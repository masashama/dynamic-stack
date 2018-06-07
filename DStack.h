struct DStack{
    unsigned int head;
    unsigned int buffer_size;
    int *buffer;
};

typedef struct DStack DStack;

DStack dstack_create();

int dstack_push(int , DStack *);
int dstack_pop(DStack *);
int dstack_peek(DStack *);

int dstack_isempty(DStack *);

int dstack_get_size(DStack *);

void dstack_debug(DStack *);

int __dstack_buffer_realloc_up(DStack *);
int __dstack_buffer_realloc_down(DStack *);
