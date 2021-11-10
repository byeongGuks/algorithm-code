#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> segTree, values, lazy;

int makeSegTree(int pos, int l, int r)
{
    if(l==r) return segTree[pos] = values[l];
    int mid = (l+r)/2;
    return segTree[pos] = min(makeSegTree(pos*2, l, mid), makeSegTree(pos*2+1, mid+1, r));
}

void lazyPropagation(int pos, int l, int r)
{
    segTree[pos] += lazy[pos];
    if(l!=r)
    {
        lazy[pos*2] = lazy[pos];
        lazy[pos*2+1] = lazy[pos];
    }
    lazy[pos] = 0;
    return ;
}

void lazyUpdate(int pos, int l, int r, int nL, int nR, int val)
{
    if(lazy[pos]!=0) lazyPropagation(pos, l, r);
    if(nR<l || r<nL) return;
    if(nL<=l && r<=nR) 
    {
        lazy[pos] = val;
        lazyPropagation(pos, l, r);
        return;
    }
    
    cout << l << ", " << r << endl;
    int mid=(l+r)/2;
    lazyUpdate(pos*2,   l,     mid, nL, nR, val);
    lazyUpdate(pos*2+1, mid+1, r,   nL, nR, val);
    segTree[pos]=min(segTree[pos*2], segTree[pos*2+1]);
}

int calcAns(int pos, int l, int r)
{
    if(segTree[pos] >= 0) return (r-l+1);
    if(l==r) return 0;

    int mid=(l+r)/2;
    return calcAns(pos*2, l, mid) + calcAns(pos*2+1, mid+1, r);
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) 
{
    int N=board.size(), M=board[0].size();
    int size = N*M;
    
    values.resize(size);
    lazy.resize(size);
    segTree.resize(size * 4);
    
    for(int y=0; y<N; ++y)
        for(int x=0; x<M; ++x)
            values[y*M + x] = board[y][x];

    makeSegTree(1, 0, size-1);
    fill(lazy.begin(), lazy.end(), 0);
    for(auto & iter : skill)
    {
        int flag = (iter[0]==1) ? -1 : 1;
        int r1=iter[1], c1=iter[2], r2=iter[3], c2=iter[4], val=iter[5]*flag;
        //for(int i=r1; i<=r2; ++i) lazyUpdate(1, 0, size-1, i*M+c1, i*M+c2, val);
    }
   
    lazyUpdate(1, 0, size-1, 0, M, -4);
    return calcAns(1, 0, size-1);
}

int main()
{
    vector<vector<int> > board = 
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    vector<vector<int>> skill = 
    {
        {1, 1, 1, 2, 2, 4},
        {1, 0, 0, 1, 1, 2},
        {2, 2, 0, 2, 0, 100}
    };
    solution(board, skill);
    return 0;
}