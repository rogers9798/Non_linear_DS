#include<bits/stdc++.h>
using namespace std;

// MIN Heap
void up_heapify(vector<int> &heap, int index) {

    if(index == 0) {
        return;
    }
    int parent_index = (index-1)/2;
    if(heap[parent_index] > heap[index]) {
        int temp = heap[parent_index];
        heap[parent_index] = heap[index];
        heap[index] = temp;
        up_heapify(heap, parent_index);
    }
    else {
        return;
    }
}

void down_heapify(vector<int> &heap, int index) {

    int smallest_index = index;
    int left_child = index*2 + 1;
    int right_child = index*2 + 2;
    if(left_child > heap.size() and right_child > heap.size()) {
        return;
    }
    if(left_child < heap.size() and heap[left_child] < heap[smallest_index]) {
        smallest_index = left_child;
    }
    if(right_child < heap.size() and heap[right_child] < heap[smallest_index]) {
        smallest_index = right_child;
    }
    if(smallest_index == index) {
        return;
    }
    swap(heap[index], heap[smallest_index]);
    down_heapify(heap, smallest_index);
}

void insert(vector<int> &heap, int key) {

    heap.push_back(key);
    up_heapify(heap, heap.size()-1);
}

void delete_peak(vector<int> &heap) {

    swap(heap[0], heap[heap.size()-1]);
    heap.pop_back();
    down_heapify(heap, 0);
}

void build_heap(vector<int> &heap) {
    // T = O(nlogn)
    for(int i=0; i<heap.size(); i++) {
        up_heapify(heap, i);
    }
}

void print(vector<int> &heap) {

    for(int i=0; i<heap.size(); i++) {
        cout<<heap[i]<<", ";
    }
    cout<<endl;
}

int main() {

    vector<int> heap;
    int n;
    cin>>n;
    for(int i=0; i<n; i++) {
        int x;
        cin>>x;
        heap.push_back(x);
        // insert(heap, x);
    }
    print(heap);
    build_heap(heap);
    print(heap);
    delete_peak(heap);
    print(heap);
    return 0;
}