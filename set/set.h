#ifndef set_h
#define set_h

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct Set {
    int32_t* array;
    size_t cap,size;
};

void set_init(struct Set*);
void set_add(struct Set*,int32_t item);
bool set_contains(struct Set*,int32_t item);
bool set_delete(struct Set*,int32_t item);
void set_free(struct Set*);
void set_print(struct Set*);

void set_difference(struct Set* , struct Set* , struct Set* );
void set_intersection(struct Set* , struct Set* , struct Set* );
void set_union(struct Set* , struct Set* , struct Set* );

#endif
