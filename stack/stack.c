#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "stack.h"

void 
stack_init(struct Stack* s) {
    s->head = NULL;
    s->size = 0;
}

void
stack_push(struct Stack* s, int32_t item) {
    struct Node* n = malloc(sizeof(struct Node));
    if (n == NULL) {
        fprintf(stderr,"alloc error");
        exit(69);
    }
    n->item = item;
    n->next = s->head;
    s->head = n;
    s->size++;
}

bool 
stack_pop(struct Stack* s, int32_t* ret) {
    if (s->size == 0) {
        return false;
    }
    *ret = s->head->item;
    struct Node* temp = s->head;
    s->head = s->head->next;    
    s->size--;
    free(temp);
    return true;
}

void 
stack_free(struct Stack* s) {
    int ret;
    while ((stack_pop(s,&ret)));
}

void 
stack_print(struct Stack* s) {
    if (s->size == 0) {
        printf("[EMPTY]\n");
        return;
    } 
    struct Node* trav = s->head;
    while (trav != NULL) {
        printf("%d ",trav->item);
        trav = trav->next;
    }
    printf("]\n");
}
