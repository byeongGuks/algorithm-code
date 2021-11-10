
// Dinic algorithm
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAX_N = 509, INF = 987654321;
int numNode, SRC, SINK;
int capacity[MAX_N][MAX_N], flow[MAX_N][MAX_N];
int level[MAX_N];

// make level graph and return true
// if can't make level graph return false
bool bfs()
{
    memset(level, -1, sizeof(level));
    level[SRC]=0;
    queue<int> que;
    que.push(SRC);
    while(!que.empty())
    {
        int here = que.front(); que.pop();
        for(int there=0; there<numNode; ++there)
        {
            int r = capacity[here][there]-flow[here][there];
            if(r<=0 || level[there]!=-1) continue;
            level[there] = level[here]+1;
            que.push(there);
        }
    }
    return level[SINK]!=-1;
}

int work[MAX_N];
int dfs(int here, int maxFlow)
{
    if(here == SINK) return maxFlow;
    for(int & there=work[here]; there<numNode; ++there)
    {
        int r = capacity[here][there] - flow[here][there];
        if(r<=0 || level[here]+1 != level[there]) continue;
        int ret = dfs(there, min(maxFlow, r));
        if(ret > 0) 
        {
            flow[here][there] += ret;
            flow[there][here] -= ret;
            return ret;
        }
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    cin >> numNode;

    vector<int> sources, sinks;
    for(int i=0; i<numNode; ++i)
    {
        int tmp; cin >> tmp;
        if(tmp==1) sources.push_back(i); // graph modeling
        else if(tmp==2) sinks.push_back(i);
    }
    for(int i=0; i<numNode; ++i)
        for(int j=0; j<numNode; ++j)
            cin >> capacity[i][j];
    
    SINK=numNode; SRC=numNode+1;
    numNode += 2;
    for(int iter : sources) capacity[SRC][iter] = INF;
    for(int iter : sinks) capacity[iter][SINK] = INF;

    int maxFlow=0;
    while(bfs())
    {
        memset(work, 0, sizeof(work));
        int ret;
        while(ret=dfs(SRC, INF))
        {
            maxFlow += ret;
        }
    }

    cout << maxFlow << endl;
    for(int i=0; i<numNode-2; ++i) // except SRC and SINK node(virtual node)
        if(level[i] != -1) cout << i+1 << " ";
    cout << endl;
    for(int i=0; i<numNode-2; ++i)
        if(level[i] == -1) cout << i+1 << " ";
    cout << endl;

    return 0;
}

