
//minimum spanning tree + LCA(lowest common ancestor)(implement by DP)
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

int numNode, numEdge;
vector<map<int, int> > graph; // <node, val>

// return MST value
vector<vector<pair<int, int> > > mstGraph;

int find(int u, vector<int> & parent)
{
    if(parent[u]==u) return u;
    else return parent[u]=find(parent[u], parent);
}

int makeMst (vector<pair<int, pair<int, int> > > & edges)
{
    sort(edges.begin(), edges.end(), 
    [](pair<int, pair<int, int> > & a, pair<int, pair<int, int> > & b) { return a.first < b.first; } 
    );

    int mstValue=0, addedEdge=0;
    vector<int> parent(numNode+1);


    for(int i=0; i<=numNode; ++i) parent[i] = i;
    mstGraph.resize(numNode+1);
    for(auto & iter : edges)
    {
        int u=iter.second.first, v=iter.second.second, val=iter.first; 
        int rU=find(u, parent), rV=find(v, parent);
        if(rU==rV) continue;
        parent[rU] = rV;

        mstGraph[u].push_back({v, val});
        mstGraph[v].push_back({u, val});
        mstValue += val;
        if(++addedEdge == numNode-1) break;
    }
    return mstValue;
}

int MAX_LEVEL;
vector<int> depth;
vector<vector<int> > ancestors, maxEdge;

void calcLcaInfo (int here, int parent, int parentE)
{
    depth[here] = depth[parent]+1;
    ancestors[here].resize(MAX_LEVEL);
    ancestors[here][0] = parent;
    maxEdge[here].resize(MAX_LEVEL);
    maxEdge[here][0] = parentE;
    for(int i=1; i<MAX_LEVEL; ++i)
    {
        int tmp = ancestors[here][i-1];
        ancestors[here][i] = ancestors[tmp][i-1];
        maxEdge[here][i] = max(maxEdge[here][i-1], maxEdge[tmp][i-1]);
    }
    
    for(int i=0; i<mstGraph[here].size(); ++i)
        if(mstGraph[here][i].first != parent) calcLcaInfo(mstGraph[here][i].first, here, mstGraph[here][i].second);
}

int findMaxEdge(int u, int v)
{
    int maxE = 0;
    if(depth[u] < depth[v]) swap(u, v);

    for(int i=MAX_LEVEL-1; i>=0; --i)
        if(depth[ancestors[u][i]] >= depth[v])
        {
            maxE = max(maxE, maxEdge[u][i]);
            u = ancestors[u][i];
        }
    if(u==v) return maxE;
    
    for(int i=MAX_LEVEL-1; i>=0; --i)
    {
        if(ancestors[u][i]!=ancestors[v][i])
        {
            maxE = max(maxE, max(maxEdge[u][i], maxEdge[v][i]));
            u=ancestors[u][i];
            v=ancestors[v][i];
        }
    }
    return max(maxE, max(maxEdge[u][0], maxEdge[v][0]));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> numNode >> numEdge;
    graph.resize(numNode+1); // 1~n까지 indexing이라 크기를 하나 늘려줌
    vector<pair<int, pair<int, int> > > edges(numEdge); // <val, <node1, node2> >
    for(auto & iter : edges)
    {
        cin >> iter.second.first >> iter.second.second >> iter.first;
        graph[iter.second.first].insert({iter.second.second, iter.first});
    }
    int mstValue = makeMst(edges);
    
    MAX_LEVEL = (int)floor(log2(numNode)); ++MAX_LEVEL;
    depth.resize(numNode+1); 
    ancestors.resize(numNode+1, vector<int> (MAX_LEVEL, 0)); 
    maxEdge.resize(numNode+1, vector<int> (MAX_LEVEL, 0)); 
    calcLcaInfo(1, 0, 0);

    int numQuery; cin >> numQuery;
    while(numQuery--)
    {
        int u, v; cin >> u >> v;
        //cout << mstValue <<", "<<graph[u].find(v)->second << ", " << findMaxEdge(u, v) << endl;
        cout << mstValue - findMaxEdge(u, v) + graph[u].find(v)->second << '\n';
    }
    return 0;
}

/*
3 3
1 2 10
2 3 5
1 3 7
*/