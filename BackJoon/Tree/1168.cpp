//segtree or treap

#include <iostream>
#include <vector>

using namespace std;

const int DUMP = -1111;
int N, K;
vector<pair<int, int> > segTree; // size, (leaf node : value, others : dump)
vector<int> deletedOrder;

void makeSegTree(int pos, int s, int e)
{
    if(s==e) 
    {
        segTree[pos]={1, s+1}; // s+1 : number of index
        return;
    }
    segTree[pos] = {e-s+1, DUMP};
    int mid = (s+e) / 2;
    makeSegTree(pos*2, s , mid);
    makeSegTree(pos*2+1, mid+1, e);
}

//retrun position of delete node
int deleteNode(int pos, int kth)
{
    --segTree[pos].first;
    if(kth==1 && segTree[pos].second != DUMP) 
    {
        deletedOrder.push_back(segTree[pos].second);
        segTree[pos].second = DUMP;
        return pos;
    }

    if(segTree[pos*2].first >= kth)  return deleteNode(pos*2, kth);
    kth -= segTree[pos*2].first;
    return deleteNode(pos*2+1, kth);
}

int calcLeftSize(int pos)
{
    int ans=0;
    while(pos != 1)
    {
        int parent = pos/2;
        if(pos%2==0) // even number
            ans += segTree[parent].first-segTree[pos].first;
        pos = parent;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> K;
    segTree.resize(4*N);

    makeSegTree(1, 0, N-1);

    int kth = K;
    for(int i=0; i<N; ++i)
    {
        kth = kth % segTree[1].first;
        if(kth==0) kth = segTree[1].first; // kth가 0이라는 것은 segTree의 마지막 원소를 찾는 다는 뜻
        int pos = deleteNode(1, kth);
        int leftSize = calcLeftSize(pos);
        if(leftSize >= K)
            kth = kth + K - 1;
        else
            kth = K-leftSize;
    }

    cout << "<";
    for(int i=0; i<deletedOrder.size()-1; ++i) cout << deletedOrder[i] << ", ";
    cout << deletedOrder[deletedOrder.size()-1] <<">"<<endl;
    return 0;
}