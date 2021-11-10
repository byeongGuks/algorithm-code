// case 나눠서 segment tree를 사용한 문제
// 최대값 최솟값을 구해야하는데 집합의 값이 변하는 경우 segtree로 해결할 수 있다!
// idea1) x축과 y축을 기준으로 같은 연산을 두번 반복해야하다면
// 함수로 만들어놓고 x y축을 한번 swap해줌으로써 해결할수 있다

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_COORDINATE = 1000001;
int numNode;
vector<int> x_values, y_values;
vector<vector<pair<int, int> > > x_pivot_point, y_pivot_point;
vector<pair<int, int> > segTree; // 구간에서 최댓값 두개 리턴

struct big3
{
    vector<int> data;
    big3() { data = vector<int>(3, 0); }
    void insert(int val)
    {
        if(val > data[0]) data[0]=val;
        sort(data.begin(), data.end());
    }
    int sum() { return data[0]+data[1]+data[2]; }
};

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

void makeSegTree(int pos, int s, int e, const vector<int> & values)
{
    if(s==e)
    {
        segTree[pos] = {values[s], 0};
        return;
    }
    int mid = (s+e) / 2;
    makeSegTree(pos*2, s, mid, values);
    makeSegTree(pos*2+1, mid+1, e, values);
    segTree[pos] = max2in4(segTree[pos*2], segTree[pos*2+1]);
}

void updateSegTree(int pos, int idx, int s, int e, int val)
{
    if(idx<s || e<idx) return;
    if(s==e) 
    {
        segTree[pos].first -= val;
        return;
    }

    int mid = (s+e)/2;
    updateSegTree(pos*2, idx, s, mid, val);
    updateSegTree(pos*2+1, idx, mid+1, e, val);
    segTree[pos] = max2in4(segTree[pos*2], segTree[pos*2+1]);
}

int calcSegTreeCase (vector<int> & values, vector<int> & pivotV, vector<vector<pair<int, int> > > & pivot_points)
{
    int ans = 0;
    makeSegTree(1, 0, MAX_COORDINATE-1, values); // make segment tree for x
    for(int i=0; i<MAX_COORDINATE; ++i) // pick y pivot
    {
        if(pivotV[i]==0) continue;

        for(const pair<int,int> & iter : pivot_points[i])
            updateSegTree(1, iter.first, 0, MAX_COORDINATE-1, iter.second);

        int ret = segTree[1].first + segTree[1].second + pivotV[i];
        ans = max(ans, ret);

        for(const pair<int,int> & iter : pivot_points[i])
            updateSegTree(1, iter.first, 0, MAX_COORDINATE-1, -iter.second); //restoration
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> numNode;
    x_values.resize(MAX_COORDINATE);
    y_values.resize(MAX_COORDINATE);
    x_pivot_point.resize(MAX_COORDINATE);
    y_pivot_point.resize(MAX_COORDINATE);
    
    for(int i=0; i<numNode; ++i)
    {
        int tx, ty, tv; 
        cin >> tx >> ty >> tv;
        x_values[tx] += tv;
        y_values[ty] += tv;
        x_pivot_point[tx].push_back({ty, tv});
        y_pivot_point[ty].push_back({tx, tv});
    }
    
    int ans = 0;
    //case 1, 2 greedy
    big3 xBig3, yBig3;
    for(int iter : x_values) xBig3.insert(iter);
    for(int iter : y_values) yBig3.insert(iter);
    ans = max(xBig3.sum(), yBig3.sum());

    //case 3, 4 segment tree
    segTree.resize(MAX_COORDINATE * 4);
    ans = max(ans, calcSegTreeCase(x_values, y_values, y_pivot_point));
    ans = max(ans, calcSegTreeCase(y_values, x_values, x_pivot_point));

    cout << ans << endl;
    return 0;
}