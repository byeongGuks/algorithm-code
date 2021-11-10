#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 1001;

int numEmployee, numTask, demerit;
int taskMatch[MAX_N];
bool adj[MAX_N][MAX_N], visited[MAX_N], canSol[MAX_N];

bool dfs(int a)
{
    if(visited[a]) return false;
    visited[a] = true;

    for(int tID=1; tID<=numTask; ++tID)
    {
        if(!adj[a][tID]) continue;
        if(taskMatch[tID]==-1 || dfs(taskMatch[tID]))
        {
            taskMatch[tID] = a;
            return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> numEmployee >> numTask >> demerit;
    memset(adj, 0, sizeof(adj));
    memset(canSol, 0, sizeof(canSol));
    for(int eID=1; eID<=numEmployee; ++eID)
    {
        int numEdge;
        cin >> numEdge;
        for(int j=0; j<numEdge; ++j)
        {
            int taskID;
            cin >> taskID;
            adj[eID][taskID] = true;
            canSol[taskID] = true;
        }
    }

    int ans = 0;
    memset(taskMatch, -1, sizeof(taskMatch));
    for(int eID=1; eID<=numEmployee; ++eID)
    {
        memset(visited, 0, sizeof(visited));
        if(dfs(eID)) ++ans;
    }

    for(int tID=1; tID<=numTask; ++tID)
    {
        if(demerit==0) break;
        if(taskMatch[tID]!=-1 || !canSol[tID]) continue;
        ++ans;
        --demerit;
    }

    cout << ans << endl;
    return 0;
}

