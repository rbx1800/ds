#ifndef hash_map_h
#define hash_map_h

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct Entry {
    bool tombstone;
    char* key;
    int32_t value;
};

struct HashMap {
    struct Entry* array;
    size_t size,cap;
};

void hashmap_init(struct HashMap*);
void hashmap_set(struct HashMap*,char* , int32_t);
bool hashmap_get(struct HashMap* ,char* , int32_t* );
bool hashmap_delete(struct HashMap* ,char* ); 
void hashmap_free(struct HashMap*);
void hashmap_print(struct HashMap*);

#endif
