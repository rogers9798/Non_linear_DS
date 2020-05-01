#include<bits/stdc++.h>
using namespace std;

int get_parent(int index) {

    return index & (index - 1);
}

int get_next(int index) {

    return index & (-index);
}

void update(int fenwick_tree[], int n, int index, int value) {

    index += 1;
    while(index <= n) {
        fenwick_tree[index] += value;
        index += index & (-index);
    }
}

int *build_fenwick_tree(int arr[], int n) {

    int *fenwick_tree = new int[n + 1];
    for(int i = 1; i <= n; i++) {
        fenwick_tree[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        update(fenwick_tree, n, i, arr[i]);
    }
    return fenwick_tree;
}

int get_sum(int fenwick_tree[], int index) {

    int sum = 0;
    index += 1;
    while(index > 0) {
        sum += fenwick_tree[index];
        index -= index & (-index);
    }
    return sum;
}

int main() {
    int n, x;
    cin>>n;
    int arr[n] = {0};;

    int *fenwick_tree = build_fenwick_tree(arr, n);
    
    cout<<"Enter the index till which you want the sum:  ";
    cin>>x;
    cout<<get_sum(fenwick_tree, x-1)<<endl;
    cout<<get_parent(7)<<endl;
    cout<<get_next(8)<<endl;

    return 0;
}

