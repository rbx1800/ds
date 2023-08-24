#ifndef binary_search_tree_h
#define binary_search_tree_h

#include <stdint.h>
#include <stdlib.h>

struct Node {
    bool link_color; // red->true, black->false
    int32_t item;
    struct Node *left,*right;
};

struct BSTree {
    struct Node* root; 
    size_t size;
};


void bst_insert(struct BSTree*,int32_t);
bool bst_search(struct BSTree*,int32_t);
void bst_remove(struct BSTree*,int32_t);
void bst_print(struct BSTree*);

#endif
