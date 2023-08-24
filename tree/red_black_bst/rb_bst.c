#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "rb_bst.h"

void
bst_init(struct BSTree* bst) {
    bst->root = NULL;
    bst->size = 0;
}

static struct Node*
alloc_node(int32_t item){
    struct Node* n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr,"malloc error\n");
        exit(69);
    }
    n->item = item;
    n->link_color = true;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static bool
is_red(struct Node* node) {
    if (node== NULL) return false;
    return node->link_color;
}

static struct Node* 
rotate_left(struct Node* node) {
    struct Node* x = node->right; 
    node->right = x->left;
    x->left= node;
    x->link_color = node->link_color;
    node->link_color = true;
    return x;
}

static struct Node* 
rotate_right(struct Node* node) {
    struct Node* x = node->left; 
    node->left = x->right;
    x->right = node;
    x->link_color = node->link_color;
    node->link_color = true;
    return x;
    
}

static void
flip_colors(struct Node* node) {
    node->left->link_color = !node->left->link_color;    
    node->right->link_color = !node->right->link_color;    
    node->link_color = !node->link_color;
}

static struct Node* 
insert_node(struct Node* node,int32_t item) {
    if (node == NULL) {
        return alloc_node(item);
    }
    int32_t x = node->item;
    if (x > item) {
        node->left = insert_node(node->left,item);
    }else if (x < item) {
        node->right= insert_node(node->right,item);
    }else {
        node->item = item;
    }

    if (is_red(node->right) && !is_red(node->left)) node = rotate_left(node);
    if (is_red(node->left) && is_red(node->left->left)) node = rotate_right(node);
    if (is_red(node->right) && is_red(node->left)) flip_colors(node);

    return node;
} 

void
bst_insert(struct BSTree* bst, int32_t item) {
    bst->root = insert_node(bst->root,item);
    bst->size++;
}

static bool
_bst_search(struct Node* node,int32_t item) {
    if (node == NULL) {
        return false;
    }
    int32_t x = node->item;
    if (x > item) {
        return _bst_search(node->left,item);
    }else if (x < item) {
        return _bst_search(node->right,item);
    }
    return true;
} 

bool
bst_search(struct BSTree* bst, int32_t item) {
    return _bst_search(bst->root,item);
}

static struct Node*
min(struct Node* node) {
    if (node->left == NULL) {
        return node;
    }
    return min(node->left);
}

struct Node*
_bst_remove(struct Node* node, int32_t item) {
    if (node == NULL) {
        return node;
    }
    int32_t x = node->item;
    if (x > item) {
        node->left = _bst_remove(node->left,item);
        return node;
    }else if (x < item) {
        node->right= _bst_remove(node->right,item);
        return node;
    }

    // found the target
    if (node->left == NULL) {
        struct Node* right = node->right;
        free(node);
        return right;
    }else if (node->right == NULL) {
        struct Node* left = node->left;
        free(node);
        return left ;
    }else {
        struct Node* m = min(node->right);
        node->item = m->item;
        node->right = _bst_remove(node->right,m->item);
        return node;
    }
}

void
bst_remove(struct BSTree* bst, int32_t item) {
    bst->root = _bst_remove(bst->root,item);
}

void static
_bst_print(struct Node* node, int indent) {
    if (node == NULL) {
        printf("%*sNULL-\n",indent,"");
        return;
    }
    printf("%*s%d:\n",indent,"",node->item); 
    _bst_print(node->right,indent+4);
    _bst_print(node->left,indent+4);
}

void
bst_print(struct BSTree* bst) {
    _bst_print(bst->root,0);
}

int
main() {
    struct BSTree bst;
    bst_init(&bst);
    bst_insert(&bst,1);
    bst_insert(&bst,2);
    bst_insert(&bst,3);
    bst_insert(&bst,4);
    bst_insert(&bst,5);
    bst_insert(&bst,6);
    bst_insert(&bst,7);
    bst_insert(&bst,8);
    bst_insert(&bst,9);
    bst_insert(&bst,10);
    bst_insert(&bst,11);
    bst_print(&bst);
}
