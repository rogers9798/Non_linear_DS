#ifndef FENWICK_TREE_H   // To make sure you don't declare the function more than once by including the header multiple times.
#define FENWICK_TREE_H

int get_parent(int index);
int get_next(int index);
void update(int fenwick_tree[], int n, int index, int value);
int *build_fenwick_tree(int arr[], int n);
int get_sum(int fenwick_tree[], int index);

#endif