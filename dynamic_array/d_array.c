#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include "d_array.h"

#define IN_BOUND(da,index) (!((index>=da->count) || (index < 0)))

static void*
allocate(void* a, size_t new_size) {
    if (new_size == 0) {
        free(a);
        return NULL;
    }
    void* res = realloc(a,sizeof(int32_t) * new_size);
    if (res == NULL) {
        fprintf(stderr,"ERROR: couldn't allocate memory");
        exit(69);
    } 
    return res;
}


void
d_array_free(struct D_Array* da) {
    allocate(da->array,0);
}

static void
d_array_resize(struct D_Array* da, size_t new_size) {
    int32_t* temp = allocate(da->array,new_size);
    da->array = temp;
    da->size = new_size;
}

void
d_array_init(struct D_Array* da) {
    da->array = NULL;
    da->count = 0;
    da->size = INIT_SIZE;
    da->array = (int32_t*)allocate(da->array,da->size);
} 

void
d_array_push_back(struct D_Array* da,int32_t item) {
    if (da->count >= da->size) {
        d_array_resize(da,da->size*2);
    } 
    da->array[da->count++] = item;
}

bool
d_array_get(struct D_Array* da, size_t index, int32_t* ret_val ) {
    if (!IN_BOUND(da,index)) {
        return false;
    }
    *ret_val = da->array[index];
    return true;
}

bool
d_array_set(struct D_Array* da, size_t index, int32_t item) {
    if (!IN_BOUND(da,index)) {
        return false;
    }
    if (da->count >= da->size) {
        d_array_resize(da,da->size*2);
    } 
    da->array[index] = item;
    return true;
}

bool
d_array_pop_back(struct D_Array* da, int32_t* ret_val) {
    if (da->count == 0) {
        return false; 
    }
    int32_t item = da->array[da->count--];
    if (da->count <= da->size / 3) {
        d_array_resize(da,da->size/2);
    }
    *ret_val = item;
    return true;
}

void
d_array_print(struct D_Array* da) {
    if (da->count == 0) {
        printf("[EMPTY]\n");
        return;
    }
    printf("[");
    for (size_t i = 0; i < da->count; i++){
        printf("%d, ",da->array[i]);
    }
    printf("]\n");
}

void
d_array_push_front(struct D_Array* da, int32_t item) {
    if (da->count >= da->size) {
        d_array_resize(da,da->size*2);
    } 
    int32_t t1 = item;
    int32_t t2;
    da->count++;
    for (size_t i = 0 ; i < da->count ; i++) {
        t2 = da->array[i];
        da->array[i] = t1;
        t1 = t2;
    }
}

bool
d_array_pop_front(struct D_Array* da, int32_t* ret_val) {
    if (da->count == 0) {
        return false; 
    }

    int32_t item = da->array[0];
    for (size_t i = 1 ; i < da->count ; i++) {
        da->array[i-1] = da->array[i];
    }

    *ret_val = item;
    da->count--;
    if (da->count <= da->size / 3) {
        d_array_resize(da,da->size/2);
    }
    return true;
}
