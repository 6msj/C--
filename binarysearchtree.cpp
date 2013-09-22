#include <iostream>
using namespace std;

typedef int item_type;

struct tree {
    item_type item;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
} _tree;

tree *search_tree(tree *l, item_type x);
tree *find_minimum(tree *t);
tree *find_maximum(tree *t);
void traverse_tree(tree *t);
void insert_tree(tree **l, item_type x, tree *parent);

int main() {
    return 0;
}

tree *search_tree(tree *l, item_type x) {
    if (l == NULL) { return NULL; }
    if (l->item == x) { return l; }

    if (x < l->item) {
        return ( search_tree(l->left, x) );
    } else {
        return ( search_tree(l->right, x) );
    }
}

tree *find_minimum(tree *t) {
    tree *min; // pointer to minimum
    if (t == NULL) { return NULL; }

    min = t;
    while(min->left != NULL) {
        min = min->left;
    }

    return min;
} 

tree *find_maximum(tree *t) {
    tree *max; // pointer to maximum
    if (t == NULL) { return NULL; }
    max = t;
    while(max->right != NULL) {
        max = max->right;
    }

    return max;
}

void traverse_tree(tree *t) {
    // traverse tree inorder
    if (t != NULL) {
        traverse_tree(t->left);
        cout << t->item;
        traverse_tree(t->right);
    }
}

void insert_tree(tree **l, item_type x, tree *parent) {
    tree *p; // temporary pointer
    if (*l == NULL) {
        p = new tree;
        p->item = x;
        p->left = p->right = NULL;
        p->parent = parent;
        *l = p;
        return;
    }

    if (x < (*l)->item) {
        insert_tree(&((*l)->left), x, *l);
    } else {
        insert_tree(&((*l)->right), x, *l);
    }

}
