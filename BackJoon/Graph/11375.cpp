//biparate matching
//이분매치에서 dfs를 할 때 우선적으로 아직 매칭 안된 노드에 매칭시켜준다면
//더 빠르게 작동할 수 있음
#include <iostream>
#include <vector>

using namespace std;

int numE, numT; //number of employer, number of task 
vector<vector<int> > graph;
vector<int> Amatch, Bmatch;
vector<bool> visited;

bool dfs(int here)
{
    if(visited[here]) return false;
    visited[here] = true;

    for(int there : graph[here])
    {
        if(Bmatch[there]==-1) 
        {
            Bmatch[there] = here;
            Amatch[here] = there;
            return true;
        }
    }
    for(int there : graph[here])
    {
        if(dfs(Bmatch[there]))
        {
            Bmatch[there] = here;
            Amatch[here] = there;
            return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> numE >> numT;
    ++numT;
    graph.resize(numE);
    for(int i=0; i<numE; ++i)
    {
        int size; cin >> size;
        for(int j=0; j<size; ++j)
        {
            int tmp; cin >> tmp;
            graph[i].push_back(tmp);
        }
    }

    int ans=0;
    Amatch.resize(numE); Bmatch.resize(numT);
    fill(Amatch.begin(), Amatch.end(), -1);
    fill(Bmatch.begin(), Bmatch.end(), -1);
    visited.resize(numE);
    for(int i=0; i<numE; ++i)
    {
        fill(visited.begin(), visited.end(), false);
        if(dfs(i)) ++ans;
    }
    cout << ans << endl;
    return 0;
}