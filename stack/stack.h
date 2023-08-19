#ifndef queue_h
#define queue_h

#include <stdint.h>
#include <stdlib.h>

struct Node {
    int32_t item; 
    struct Node* next;
};

struct Stack {
    struct Node *head;
    size_t size;
};

void stack_init(struct Stack*);

void stack_push(struct Stack*, int32_t );
bool stack_pop(struct Stack*, int32_t* );

void stack_free(struct Stack*);

void stack_print(struct Stack*);


#endif
