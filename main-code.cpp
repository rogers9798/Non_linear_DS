#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class FenwickTree 
{
    private:
    vector<int> fenwick;  // binary indexed tree
    int n;

    public:
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
    obj.update(4,2);
    ans = obj.sum(7);
    cout<<ans<<endl;

    cout<<obj.getParent(11)<<endl;
    cout<<obj.getNext(11)<<endl;

}