#include<iostream>
#include<bits/stdc++.h>
using namespace std;

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

int main()
{
    vector<int> arr;
    arr.push_back(1);
    arr.push_back(7);
    arr.push_back(3);
    arr.push_back(0);
    arr.push_back(5);
    arr.push_back(8);
    arr.push_back(3);
    arr.push_back(2);
    arr.push_back(6);
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(1);
    arr.push_back(4);
    arr.push_back(5);

    FenwickTree obj = FenwickTree(arr);
    int ans = obj.sum(7);
    cout<<ans<<endl;
    
    cout<<obj.getParent(11)<<endl;
    cout<<obj.getNext(11)<<endl;
    obj.print();

    arr.push_back(9);
    FenwickTree f2 = obj.copyNupdate(arr);
    cout<<"New Fenwick Tree : "<<endl;
    f2.print();

    list<FenwickTree>ft;
    ft.push_back(obj);
    ft.push_back(f2);

    ft.front().print();
    ft.back().print();
}