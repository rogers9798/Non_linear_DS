#include<iostream>
#include<vector>
using namespace std;

struct Node {

    int value;
    int src;
    int des;
};

void down_heapify(vector<Node> &heap, int index) {

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

Node delete_peak(vector<Node> &heap) {

    Node temp = heap[0];
    swap(heap[0], heap[heap.size()-1]);
    heap.pop_back();
    down_heapify(heap, 0);
    return temp;
}

void build_heap_optimized(vector<Node> &heap) {
    // T = O(n)
    for(int i=heap.size()-1; i>=0; i--) {
        down_heapify(heap, i);
    }
}

void print(vector<Node> &heap) {

    for(int i=0; i<heap.size(); i++) {
        cout<<heap[i].value<<", ";
    }
    cout<<endl;
}

class FenwickTree 
{
    public:
    vector<int> fenwick;  // binary indexed tree
    int n;

    FenwickTree(vector<int> a) 
    {
        this->n = a.size();
        fenwick.assign(n,0);

        for (int i = 0; i < a.size(); i++)
            update(i, a[i]);
    }

    int sum(int r) 
    {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += fenwick[r];
        return ret;
    }

    int sum(int l, int r) 
    {
        return sum(r) - sum(l - 1);
    }

    void update(int idx, int delta) 
    {
        for (; idx < n; idx = idx | (idx + 1))
            fenwick[idx] += delta;
    }

    int getParent(int pos) 
    {
        int temp = pos & (-pos);
        return pos-temp;
    }

    int getNext(int pos) 
    {
        int temp = pos & (-pos); 
        return temp+pos;
    }

    FenwickTree copyNupdate(vector<int>arr)
    {
        FenwickTree obj = FenwickTree(arr);
        return obj;
    }

    void print()
    {
        for(int i=0;i<n;i++)
            cout<<fenwick[i]<<" ";
        cout<<endl;
    }
};

struct node
{
    int e; // end
    int wt;
    struct node *next;
};

struct list
{
    struct node *head;
};

class graph
{
public:
    int v; // vertices
    struct list *arr;
    vector<bool> visited;
    vector<int> visitFrom;
    vector<FenwickTree> ft;
    vector<int> visitCost;
    vector<Node> heap;

    graph(int vert)
    {
        this->v = vert;
        arr = new list[vert];
        // f=new FenwickTree(visited);
        for (int i = 0; i < vert; i++)
        {
            visited.push_back(false);
            visitFrom.push_back(0);
            visitCost.push_back(0);
            arr[i].head = NULL;
        }
    }

    node *new_node(int E, int W)
    {
        struct node *temp = new (node);
        temp->e = E;
        temp->wt = W;
        temp->next = NULL;
        return temp;
    }

    void add_edge(int s, int e, int w) // start and end
    {
        struct node *ptr1 = new_node(e, w);
        ptr1->next = arr[s].head;
        arr[s].head = ptr1;

        struct node *ptr2 = new_node(s, w);
        ptr2->next = arr[e].head;
        arr[e].head = ptr2;
    }

    int getPathCost(int s,int e){
        struct node *ptr = arr[s].head;
            while (ptr)
            {
                if(ptr->e==e){
                    return ptr->wt;
                }
                ptr = ptr->next;
            }
    }

    vector<int> pathByVisited(int index){
        vector<int> path;
        do{
            path.insert(path.begin(),getPathCost(visitFrom[index],index));
            index=visitFrom[index];
        }while(index!=0);
        return path;
    }

    vector<int> findUnvisitedNeighbour(int index){
        vector<int> unvisited;
        struct node *ptr = arr[index].head;
            while (ptr)
            {
                if(!visited[ptr->e]){
                    unvisited.push_back(ptr->e);
                }
                ptr = ptr->next;
            }
        return unvisited;
    }

    bool allVisited(){
        for(auto it=visited.begin();it!=visited.end();it++){
            if(!*it){
                return false;
            }
        }
        return true;
    }

    void findNextSelectedNode(int index){
        vector<int> unvisited = findUnvisitedNeighbour(index);
        for(int i=0;i<unvisited.size();i++){
            vector<int> path=pathByVisited(index);
            cout<<"path for "<<unvisited[i]<<":- ";
            path.push_back(getPathCost(index,unvisited[i]));
            
            for(int j=0;j<path.size();j++){
                cout<<path[j]<<" ";
            }
            cout<<endl;
            // create fenwick tree for path array here
            FenwickTree obj = FenwickTree(path);
            // push fenwick tree to list of objects here
            ft.push_back(obj);
            // add {cost,path[-2],path[-1]} to min heap
            Node obj1;
            obj1.value = obj.sum(path.size()-1);
            obj1.des = unvisited[i];
            obj1.src = index;
            heap.push_back(obj1);
        }
        // create heap
        build_heap_optimized(heap);
        // pop from min heap and delete the fenwick tree from list of object
        Node val;
        if(!allVisited()){
        do{
            val = delete_peak(heap);
            for(auto it=heap.begin();it!=heap.end();it++){
                if(it->value==val.value && it->des==val.des && it->src==val.src){
                    heap.erase(it);
                    break;

                }
            }
        }while(visited[val.des]!=false && heap.size()!=0 && !allVisited());
        cout<<"value= " <<val.value<<" source= "<<val.src<<" dest="<<val.des<<endl;
        visited[val.des]= true;
        visitFrom[val.des] = val.src;
        visitCost[val.des] = val.value;
        // for(int x=0;x<v;x++){
        //     cout<<visited[x]<<",";
        // }
        findNextSelectedNode(val.des);
        }
        return;
    }

    void dijkstra(){
        for(int i=0;i<v;i++){
            visited[i]=true;
            if(i==0){
                findNextSelectedNode(0);
            }
            else{
                visitFrom[i]=-1;
            }
        }
    }

    void display()
    {
        int i;
        cout << "\nAdjacency List \n";
        for (i = 0; i < v; i++)
        {
            struct node *ptr = arr[i].head;
            cout << "\nVertex " << i << " - ";
            while (ptr)
            {
                cout << ptr->e << "  wt :" << ptr->wt << ", ";
                ptr = ptr->next;
            }
            cout << "\n";
        }
    }
};

int main(){
    int n;
    cin>>n;
    graph g(n);
    int edges;
    cin>>edges;
    int s,d,w;
    for(int i=0;i<edges;i++){
        cin>>s>>d>>w;
        g.add_edge(s,d,w);
    }
    g.dijkstra();
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<g.visitCost[i]<<" ";
    }
    cout<<endl;
    // g.display();
    return 0;
}