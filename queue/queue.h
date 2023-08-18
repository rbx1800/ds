#ifndef queue_h
#define queue_h

#include <stdint.h>
#include <stdlib.h>

struct Node {
    int32_t item; 
    struct Node* next;
};

struct Queue {
    struct Node *head,*tail;
    size_t size;
};

void queue_init(struct Queue*);

void queue_enqueue(struct Queue*, int32_t );
bool queue_dequeue(struct Queue*, int32_t* );

void queue_free(struct Queue*);

void queue_print(struct Queue*);


#endif
