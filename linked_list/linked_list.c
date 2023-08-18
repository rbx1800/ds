#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "linked_list.h"

struct Node {
    int32_t item;
    struct Node *next, *prev;
};

static struct Node* 
alloc_node(int32_t item) {
    struct Node* n = malloc(sizeof(struct Node));
    if ( n == NULL ) {
        fprintf(stderr,"ERROR: malloc\n");
        exit(69);
    }
    n->item = item;
    n->next = NULL;
    n->prev = NULL;
    return n;
}


void
linked_list_init(struct LinkedList* ll) {
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
}

void
linked_list_push_head(struct LinkedList* ll, int32_t item) {
    struct Node* node = alloc_node(item);
    if (ll->size == 0) {
        ll->head = node; 
        ll->tail = node;
        ll->size++;
        return;
    }
    ll->head->prev = node;
    node->next = ll->head;
    node->prev = NULL;
    ll->head = node;
    ll->size++;
}

void
linked_list_push_tail(struct LinkedList* ll, int32_t item) {
    struct Node* node = alloc_node(item);
    if (ll->size == 0) {
        ll->head = node; 
        ll->tail = node;
        ll->size++;
        return;
    }
    ll->tail->next = node;
    node->prev = ll->tail;
    node->next = NULL;
    ll->tail = node;
    ll->size++;
}

bool
linked_list_pop_tail(struct LinkedList* ll, int32_t* ret_val) {
    if (ll->size == 0) {
        return false;
    }
    struct Node* temp = ll->tail;
    *ret_val = ll->tail->item;
    ll->tail = ll->tail->prev;
    if (ll->tail) {
        ll->tail->next = NULL;
    }
    ll->size--;
    free(temp);
    return true;
}


bool
linked_list_pop_head(struct LinkedList* ll, int32_t* ret_val) {
    if (ll->size == 0) {
        return false;
    }
    struct Node* temp = ll->head;
    *ret_val = ll->head->item;
    ll->head = ll->head->next;
    if (ll->head) {
        ll->head->prev = NULL;
    } 
    ll->size--;
    free(temp);
    return true;
}

void 
linked_list_print(struct LinkedList* ll) {
    if (ll->size == 0) {
        printf("<EMPTY>\n");
        return;
    }
    struct Node* trav = ll->head;
    while (trav != NULL) {
        printf("%d <> ",trav->item);
        trav =  trav->next;
    }
    printf("\n");
}
