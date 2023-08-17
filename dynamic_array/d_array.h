#ifndef d_array_h
#define d_array_h

#include <stdint.h>
#include <stdlib.h>


#define INIT_SIZE 8

struct D_Array {
    int32_t* array; 
    size_t size,count;
};

void d_array_free(struct D_Array*);
void d_array_init(struct D_Array*);

bool d_array_get(struct D_Array*,size_t,int32_t*);
bool d_array_set(struct D_Array* , size_t , int32_t );


void d_array_push_back(struct D_Array*,int32_t);
bool d_array_pop_back(struct D_Array*,int32_t*);

void d_array_push_front(struct D_Array*,int32_t);
bool d_array_pop_front(struct D_Array*,int32_t*);

void d_array_print(struct D_Array*);

#endif
