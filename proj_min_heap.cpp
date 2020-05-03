#include<bits/stdc++.h>
using namespace std;

struct node {

    int value;
    int src;
    int des;
};

void down_heapify(vector<node> &heap, int index) {

    int smallest_index = index;
    int left_child = index*2 + 1;
    int right_child = index*2 + 2;
    if(left_child > heap.size() and right_child > heap.size()) {
        return;
    }
    if(left_child < heap.size() and heap[left_child].value < heap[smallest_index].value) {
        smallest_index = left_child;
    }
    if(right_child < heap.size() and heap[right_child].value < heap[smallest_index].value) {
        smallest_index = right_child;
    }
    if(smallest_index == index) {
        return;
    }
    swap(heap[index], heap[smallest_index]);
    down_heapify(heap, smallest_index);
}

node delete_peak(vector<node> &heap) {

    node temp = heap[0];
    swap(heap[0], heap[heap.size()-1]);
    heap.pop_back();
    down_heapify(heap, 0);
    return temp;
}

void build_heap_optimized(vector<node> &heap) {
    // T = O(n)
    for(int i=heap.size()-1; i>=0; i--) {
        down_heapify(heap, i);
    }
}

void print(vector<node> &heap) {

    for(int i=0; i<heap.size(); i++) {
        cout<<heap[i].value<<", ";
    }
    cout<<endl;
}

int main() {

    vector<node> heap;
    node obj;
    int n;
    cin>>n;
    for(int i=0; i<n; i++) {
        cin>>obj.value;
        cin>>obj.src;
        cin>>obj.des;
        heap.push_back(obj);
    }
    build_heap_optimized(heap);
    print(heap);
    node val = delete_peak(heap);
    cout<<val.value<<endl;
    
    return 0;
}