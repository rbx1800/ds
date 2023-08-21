#ifndef heap_h
#define heap_h

#include <stdint.h>
#include <stdlib.h>

struct Heap {
    int32_t* array;
    size_t cap,size;
};

void heap_init(struct Heap*);
void heap_add(struct Heap*,int32_t);
bool heap_remove(struct Heap* , int32_t* );
void heap_print(struct Heap*);

#endif
