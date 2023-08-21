#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "heap.h"

#define INIT_CAP 8

static void
resize(struct Heap* h,size_t new_size) {
    h->array = realloc(h->array,sizeof(struct Heap)*new_size);
    if (h->array == NULL) {
        fprintf(stderr,"malloc error\n");
        exit(69);
    }
    h->cap = new_size;
}

static void
up(struct Heap* h, int idx, int bound) {
    for(;;) {
        int p_idx = (idx-1);
        if (p_idx < bound) {
            break;
        }
        p_idx /= 2;
        if (h->array[p_idx] > h->array[idx]) {
            break;
        }
        int32_t t = h->array[p_idx];
        h->array[p_idx] = h->array[idx];
        h->array[idx] = t;
        idx = p_idx;
    }
}

static void
down(struct Heap* h, int idx,int bound) {
    for(;;) {
        int c_idx1 = (idx*2)+1;
        int c_idx2 = (idx*2)+2;
        if (c_idx1 >= bound) {
            break;
        }
        int i = c_idx1;
        if ( c_idx2 < bound && h->array[i] < h->array[c_idx2]) {
            i = c_idx2; 
        }
        if (h->array[i] < h->array[idx]) {
            break;
        }

        int32_t t = h->array[i];
        h->array[i] = h->array[idx];
        h->array[idx]= t;
        idx = i;    
    }
}

void 
heap_init(struct Heap* h){
    h->cap = INIT_CAP;
    h->size = 0 ;
    h->array = malloc(sizeof(int32_t)*h->cap);
    if (h->array == NULL) {
        fprintf(stderr,"malloc error\n");
        exit(69);
    }
}

void 
heap_add(struct Heap* h,int32_t item){
    if (h->cap == h->size) {
        resize(h,h->cap*2);
    }
    h->array[h->size] = item;
    h->size++;
    up(h,h->size-1,0);
}

bool 
heap_remove(struct Heap* h, int32_t* item) {
    if (h->size == 0) {
        return false;
    }
    *item = h->array[0];
    h->array[0] = h->array[--h->size];
    down(h,0,h->size);
    if (h->size < h->cap / 3) {
        resize(h,h->cap/2);
    }
    return true;
} 

void 
heap_print(struct Heap* h){
    if (h->size == 0) {
        printf("[EMPTY]\n");
        return;
    }
    printf("[");
    for (int i =0;i < h->size;i++) {
        printf("%d ",h->array[i]);
    }
    printf("]\n");
}
