#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "queue.h"

void 
queue_init(struct Queue* q) {
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void
queue_enqueue(struct Queue* q, int32_t item) {
    struct Node* n = malloc(sizeof(struct Node));
    if (n == NULL) {
        fprintf(stderr,"alloc error");
        exit(69);
    }
    n->item = item;
    if (q->size == 0) {
        q->head = n;
        q->tail = n;
        q->size++;
        return;
    }
    n->next = NULL;
    q->tail->next = n;
    q->tail = n;
    q->size++;
}

bool 
queue_dequeue(struct Queue* q, int32_t* ret) {
    if (q->size == 0) {
        return false;
    }
    *ret = q->head->item;
    struct Node* temp = q->head;
    q->head = q->head->next;    
    q->size--;
    free(temp);
    return true;
}

void 
queue_free(struct Queue* q) {
    int ret;
    while ((queue_dequeue(q,&ret)));
}

void 
queue_print(struct Queue* q) {
    if (q->size == 0) {
        printf("[EMPTY]\n");
        return;
    } 
    struct Node* trav = q->head;
    while (trav != NULL) {
        printf("%d ",trav->item);
        trav = trav->next;
    }
    printf("]\n");
}
