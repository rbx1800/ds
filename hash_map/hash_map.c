#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_map.h"

#define INIT_CAP 8

// string -> int32

static size_t 
hash_function(char* string){
    int hash_value = 5381;
    for (char* s= string ; *s != '\0'; s = s+1) {
        hash_value = ((hash_value << 5) + hash_value) + *s;
    }
    return hash_value;
}


void 
hashmap_init(struct HashMap* hm) {
    hm->size = 0;
    hm->cap = INIT_CAP;
    hm->array = (struct Entry*)malloc(sizeof(struct Entry)*hm->cap);
    for (size_t i = 0 ; i < hm->cap; i++) {
        hm->array[i].tombstone = false;
        hm->array[i].key = NULL;
    }

}


static struct Entry*
find_entry(struct HashMap* hm, char* key) {
    size_t idx = hash_function(key) % hm->cap; 
    struct Entry* tombstone = NULL;
    for (;;) {
        struct Entry* e = &hm->array[idx];
        if (e->key == NULL) {
            if (e->tombstone) {
                tombstone = e; 
            }else {
                return tombstone != NULL ? tombstone : e;
            }
        }else if (strcmp(e->key, key) == 0) {
            return e; 
        }
        idx = (idx + 1) % hm->cap;
    }
}


static void
resize(struct HashMap* hm,size_t new_cap) {
    struct Entry* temp = hm->array;
    size_t temp_cap = hm->cap;
    struct Entry* new_array = malloc(sizeof(struct Entry)*new_cap);
    if (new_array == NULL) {
        fprintf(stderr,"malloc error");
        exit(69);
    }
    hm->array = new_array;
    hm->cap = new_cap;
    for (int i = 0 ; i < temp_cap; i++) {
        if (temp[i].key == NULL) {
            continue;
        }
        hashmap_set(hm,temp[i].key,temp[i].value);
    }
    free(temp);
}

void 
hashmap_set(struct HashMap* hm, char* key , int32_t value) {
    if (hm->size == hm->cap) {
        resize(hm,hm->cap*2);
    } 
    struct Entry* e = find_entry(hm,key);
    if (e->key == NULL && !e->tombstone) {
       hm->size++; 
    }
    e->key = key;
    e->value = value;
    e->tombstone = false;
}

bool
hashmap_get(struct HashMap* hm,char* key, int32_t* value) {
    if (hm->size == 0) {
        return false;
    }
    struct Entry* e = find_entry(hm,key);
    if (e->key == NULL || e->tombstone) {
        return false;
    }
    *value = e->value; 
    return true;
}

bool
hashmap_delete(struct HashMap* hm,char* key) {
    if (hm->size == 0) {
        return false;
    }
    struct Entry* e = find_entry(hm,key);
    if (e->key == NULL || e->tombstone) {
        return false;
    }
    e->tombstone = true;
    e->key = NULL;
    return true;

}

void
hashmap_free(struct HashMap* hm) {
    free(hm->array);
}

void 
hashmap_print(struct HashMap* hm) {
    if (hm->size == 0) {
        printf("<EMPTY>\n");
        return;
    }
    printf("<");
    for (int i = 0 ; i < hm->cap; i++) {
        if (hm->array[i].key == NULL) {
            continue;
        } 
        printf("%s:%d,",hm->array[i].key,hm->array[i].value);
    }

    printf(">\n");
}
