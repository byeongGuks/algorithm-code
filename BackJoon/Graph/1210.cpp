// 최대 유량 문제 && 그래프 모델링

#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int MAX_INT = 2147483647; // (1<<30)-1
int maxNodeID, source, sink;
int capacity[401][401], flow[401][401];
int level[401];

// make level graph
bool bfs()
{
    memset(level, -1, sizeof(level));
    queue<int> que;
    que.push(source);
    level[source] = 0;
    while(!que.empty())
    {
        int here = que.front();
        que.pop();

        for(int there=0; there<=maxNodeID; ++there)
            if(level[there]==-1 && capacity[here][there]-flow[here][there] > 0)
            {
                level[there] = level[here] + 1;
                que.push(there);
            }
    }
    return level[sink]!=-1;
}

int worked[401];
int dfs(int here, int maxF)
{
    if(here == sink) return maxF;

    int ret = 0;
    for(int & there=worked[here]; there<=maxNodeID; ++there)
    {
        int r = capacity[here][there] - flow[here][there];
        if(r>0 && level[here]+1 == level[there])
        {
            ret = dfs(there, min(maxF, r));
            if(ret != 0)
            {
                flow[here][there] += ret;
                flow[there][here] -= ret;
                return ret;
            }
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    //initalization
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    int n, m;
    cin >> n >> m >> source >> sink;
    maxNodeID = n*2;
    source = source*2-1;
    sink = sink*2;
    // graph modeling
    for(int i=0; i<n; ++i)
    {
        int gateFee, from=(i+1)*2-1, to=(i+1)*2; 
        cin >> gateFee;
        capacity[from][to] = gateFee;
    }
    for(int i=0; i<m; ++i)
    {
        int a, b;
        cin >> a >> b;
        capacity[a*2][b*2-1] = capacity[b*2][a*2-1] = MAX_INT;
    }

    int maxFlow=0, result;
    while(bfs())
    {
        memset(worked, 0, sizeof(worked));
        while(result = dfs(source, MAX_INT)) maxFlow += result;
    }

    //find min cut
    queue<int> que;
    que.push(source);
    memset(level, -1, sizeof(level));
    vector<bool> visited(401, false);
    visited[source]=true;
    while(!que.empty())
    {
        int here = que.front();
        que.pop();  

        for(int there=0; there<=maxNodeID; ++there)
            if(visited[there]==false && capacity[here][there]-flow[here][there] > 0)
            {
                visited[there] = true;
                que.push(there);
            }
    }
    for(int i=1; i<= maxNodeID; i+=2)
        if(visited[i] && !visited[i+1]) cout << ((i+1)/2) << ' ';
    cout << endl;
}