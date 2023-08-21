#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "set.h" 

#define INIT_CAP 8

static void
resize(struct Set* set, size_t new_size) {
    set->array = realloc(set->array, sizeof(int32_t) * new_size);
    set->cap = new_size;
    if (set->array == NULL) {
        fprintf(stderr,"malloc error\n");
        exit(69);
    }
}

static size_t 
partition(int32_t* array ,int low, int high) { 
    int left = low;
    int right = high - 1;
    int32_t pivot = array[high];
    for(;;) {
        for (;left <= right && array[left] <= pivot;) left++;
        for (;left <= right && array[right] >= pivot;) right--;
        if (left > right) break;
        int32_t t = array[left];
        array[left] = array[right];
        array[right] = t;
    }
    int32_t t = array[left];
    array[left] = pivot;
    array[high] = t ;
    return left;
}

static void
sort(int32_t* array ,int low, int high) {
    if (low >= high) {
        return;
    } 
    size_t pivot = partition(array,low,high);
    sort(array,low,pivot-1);
    sort(array,pivot+1,high);
}

static int
search(int32_t* array,int32_t item,int low,int high) {
    for (;low <= high;) {
        int mid = (low+high) / 2;
        if (array[mid] == item) {
            return mid; 
        }else if (array[mid] < item) {
            low = mid+1;
        }else {
            high = mid-1;
        }
    }
    return -1;
}

void
set_init(struct Set* set) {
    set->cap = INIT_CAP;
    set->size = 0;
    set->array = malloc(sizeof(int32_t) * set->cap);
    if (set->array == NULL) {
        fprintf(stderr,"malloc error\n");
        exit(69);
    }
}

void 
set_add(struct Set* set,int32_t item) {
    if (set_contains(set,item)) {
        return; 
    }
    if (set->cap == set->size) {
        resize(set,set->cap*2);
    }
    set->array[set->size++] = item;
    sort(set->array,0,set->size-1);
}

bool
set_contains(struct Set* set, int32_t item) {
    if (set->size ==0) {
        return false;
    }
    int idx = search(set->array,item,0,set->size-1);
    return idx != -1 ? true : false;
}

bool
set_delete(struct Set* set, int32_t item) {
    if (set->size ==0) {
        return false;
    }
    int idx = search(set->array,item,0,set->size-1);
    if (idx == -1) {
        return false;
    }
    printf("idx=%d\n",idx);
    set->array[idx] = set->array[set->size-1];
    set->size--;
    if (set->size < set->cap / 3) {
        resize(set,set->cap / 2); 
    }
    sort(set->array,0,set->size-1);
    return true;
}


void
set_print(struct Set* set) {
    if (set->size ==0) {
        printf("()\n");
        return;
    }
    printf("(");
    for (int i= 0 ; i < set->size; i++) {
        printf("%d ",set->array[i]);
    }
    printf(")\n");
}

void
set_free(struct Set* set) {
    free(set->array);
}


void 
set_difference(struct Set* s1, struct Set* s2, struct Set* s3) {
    for (int i = 0; i < s1->size; i++) {
        if (!set_contains(s2,s1->array[i])) {
            set_add(s3,s1->array[i]);
        }
    }
    for (int i = 0; i < s2->size; i++) {
        if (!set_contains(s1,s2->array[i])) {
            set_add(s3,s2->array[i]);
        }
    }
}

void 
set_intersection(struct Set* s1, struct Set* s2, struct Set* s3) {
    for (int i = 0; i < s1->size; i++) {
        if (set_contains(s2,s1->array[i])) {
            set_add(s3,s1->array[i]);
        }
    }
}

void 
set_union(struct Set* s1, struct Set* s2, struct Set* s3) {
    for (int i = 0; i < s1->size; i++) {
        set_add(s3,s1->array[i]);
    }
    for (int i = 0; i < s2->size; i++) {
        set_add(s3,s2->array[i]);
    }
}
