#include <string>
#include <vector>
#include <queue>

using namespace std;


vector<int> parent;
vector<vector<int>> children;
vector<long long> subSum, glb_value;

void calcParentChild(const vector<vector<int>> & edges, int numNode);
long long calcSubSum(int node);
void initSubSum(int numNode);
void updateSubSum(int u, int w, long long rmv);

vector<long long> solution(vector<int> values, vector<vector<int>> edges, vector<vector<int>> queries) 
{
    glb_value.resize(values.size()+1);
    for(int i=0; i<values.size(); ++i) glb_value[i+1] = values[i];
    calcParentChild(edges, values.size());
    initSubSum(values.size());
    
    vector<long long> ans;
    for(int i=0; i<queries.size(); ++i)
    {
        int u=queries[i][0], w=queries[i][1];
        if(w==-1)
            ans.push_back(subSum[u]);
        else
            updateSubSum(u, w, glb_value[u]);
    }
    
    return ans;
}

void calcParentChild(const vector<vector<int>> & edges, int numNode)
{
    parent.resize(numNode+1); 
    children.resize(numNode+1);
    vector<vector<int>> adj;
    adj.resize(numNode+1);
    for(int i=0; i<edges.size(); ++i)
    {
        int a=edges[i][0], b=edges[i][1];
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    //bfs 
    vector<bool> discovered(numNode+1, false);
    discovered[1]=true;
    queue<int> que;
    que.push(1);
    while(!que.empty())
    {
        int here = que.front();
        que.pop();
        for(int there : adj[here])
        {
            if(discovered[there]) continue;
            discovered[there] = true;
            que.push(there);
            parent[there]=here; // make vector<int> parent
            children[here].push_back(there); // make vector<vector<int>> children
        }
    }
}

long long calcSubSum(int node)
{
    subSum[node] = glb_value[node];
    for(int i : children[node])
        subSum[node] += calcSubSum(i);
    return subSum[node];
}
void initSubSum(int numNode)
{
    subSum.resize(numNode+1);
    calcSubSum(1);
}

void updateSubSum(int u, int w, long long rmv)
{
    if(u==1)
    {
        subSum[1] += w - rmv;
        glb_value[1] = w;
    }
    else
    {
        subSum[u] += glb_value[parent[u]] - rmv;
        glb_value[u] = glb_value[parent[u]];
        updateSubSum(parent[u], w, rmv);
    }
}


