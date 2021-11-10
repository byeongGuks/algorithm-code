#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_SIZE = (1<<18)+1;
vector<int> num;
vector<int> numPosition;
vector<pair<int, int> > segTree;

pair<int, int> max2in4 (const pair<int,int> & a, const pair<int,int> & b)
{
    int arr[4];
    arr[0]=a.first;
    arr[1]=a.second;
    arr[2]=b.first;
    arr[3]=b.second;
    sort(arr, arr+4);
    return {arr[3], arr[2]};
}

void makeSegTree (int s, int e, int pos)
{
    if(s==e)
    {
        segTree[pos] = {num[s], -1};
        numPosition[s] = pos;
        return;
    }
    
    int mid = (s+e)/2;
    makeSegTree(s, mid, 2*pos);
    makeSegTree(mid+1, e, 2*pos+1);

    segTree[pos] = max2in4(segTree[2*pos], segTree[2*pos+1]);
}


void updateSegTree(int index, int newVal, int node, int nodeL, int nodeR)
{
    if(index<nodeL || nodeR<index) return;
    if(nodeL==nodeR) 
    {
        segTree[node].first = newVal;
        return;
    }

    int mid = (nodeL + nodeR) / 2;
    updateSegTree(index, newVal, node*2, nodeL, mid);
    updateSegTree(index, newVal, node*2+1, mid+1, nodeR);
    segTree[node] = max2in4(segTree[node*2], segTree[node*2+1]);
}

void updateSegTree(int pos, int val)
{
    if(pos==0) return;

    pair<int, int> & tNode = segTree[pos];
    if(tNode.second > tNode.first) swap(tNode.first, tNode.second);
    if(tNode.second >= val) return;
    
    if(tNode.second != -1) tNode.second = val;
    else tNode.first = val;

    if(tNode.second > tNode.first) swap(tNode.first, tNode.second);
    updateSegTree(pos/2, val);
}

pair<int, int> query(int l, int r, int nodeL, int nodeR, int node)
{
    if(r<nodeL || nodeR<l) return {-1, -1};

    if(l<=nodeL && nodeR<=r) return segTree[node];
    
    int mid = (nodeL+nodeR) / 2;
    pair<int, int> a = query(l, r, nodeL, mid, 2*node);
    pair<int, int> b = query(l, r, mid+1, nodeR, 2*node+1);
    return max2in4(a, b);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    num.resize(n);
    numPosition.resize(n);
    segTree.resize(MAX_SIZE);
    for(int & iter : num) cin >> iter;
    makeSegTree(0, n-1, 1);
    
    int numQuery; cin >> numQuery;
    for(int q=0; q<numQuery; ++q)
    {
        int a, b, c; cin >> a >> b >> c;
        switch(a)
        {
            case 1 :
                //updateSegTree(numPosition[b-1], c);
                updateSegTree(b-1, c, 1, 0, n-1);
                break;
            case 2 :
                pair<int, int> a = query(b-1, c-1, 0, n-1, 1);
                cout << a.first + a.second << "\n";
                break;
        }
    }
    return 0;
}