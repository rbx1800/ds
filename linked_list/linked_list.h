#ifndef linked_list_h
#define linked_list_h
#include <stdlib.h>

struct LinkedList {
    struct Node *head, *tail; 
    size_t size;
};

void linked_list_init(struct LinkedList*);

void linked_list_push_head(struct LinkedList*,int32_t);
void linked_list_push_tail(struct LinkedList*, int32_t); 

bool linked_list_pop_tail(struct LinkedList* , int32_t* );
bool linked_list_pop_head(struct LinkedList* , int32_t* );

void  linked_list_print(struct LinkedList*);

#endif
