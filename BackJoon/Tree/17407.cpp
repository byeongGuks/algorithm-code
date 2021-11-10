//segment tree, laxy propagation

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<bool> arr;
vector<int> segTree; //min value
vector<int> lazy;

void makeArr()
{
    string str; cin >> str;
    arr.resize(0);
    for(char & iter : str)
        arr.push_back(iter=='(');
}

void lazyPropagation(int pos, int s, int e)
{
    if(lazy[pos]==0) return;
    segTree[pos] += lazy[pos];
    if(s!=e)
    {
        lazy[pos*2] += lazy[pos];
        lazy[pos*2+1] += lazy[pos];
    }
    lazy[pos] = 0;
}


void makeSegTree(int pos, int s, int e, const vector<int> & values)
{
    if(s==e)
    {
        segTree[pos] = values[s];
        return;
    }
    int mid = (s+e)/2;
    makeSegTree(pos*2, s, mid, values);
    makeSegTree(pos*2+1, mid+1, e, values);

    segTree[pos] = min(segTree[pos*2], segTree[pos*2+1]);
}

void updateRange(int pos, int s, int e, int rS, int lazyValue) //rE==values.size()-1
{
    lazyPropagation(pos, s, e);
    if(e<rS) return;
    if(rS<=s)
    {
        lazy[pos] += lazyValue;
        lazyPropagation(pos, s, e);
        return;
    }

    int mid = (s+e) / 2;
    updateRange(pos*2, s, mid, rS, lazyValue);
    updateRange(pos*2+1, mid+1, e, rS, lazyValue);
    segTree[pos]= min(segTree[pos*2], segTree[pos*2+1]);
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    makeArr();
    vector<int> values(arr.size());
    values[0] = arr[0] ? 1 : -1;
    for(int i=1; i<arr.size(); ++i) values[i] = values[i-1] + (arr[i] ? 1 : -1);
    int valance = values.back();

    segTree.resize(values.size() * 4);
    lazy.resize(values.size() * 4);
    makeSegTree(1, 0, values.size()-1, values);

    int numQuery; cin >> numQuery;
    int ans = 0;
    for(int i=0; i<numQuery; ++i)
    {
        int idx; cin >> idx; --idx;
        int lazyValue = arr[idx] ? -2 : 2;
        valance += lazyValue;
        arr[idx] = !arr[idx];
        updateRange(1, 0, values.size()-1, idx, lazyValue);
        if(segTree[1] > -1 && valance==0) ++ans;
    }
    cout << ans << endl;
    return 0;
}

