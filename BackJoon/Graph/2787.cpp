// bipartite matching O(V*E)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> aMatch, bMatch, maxLimit, minLimit; // a : index, b : value, minLimit[aidx] <= e =<maxLimit[aidx] : a idx 위치 수가 연결될 수 있는 수의 범위
vector<int> minCandidate, maxCandidate; //minCandidate[bidx] <= e <= minCandidate[bidx] : b idx 수와 연결 될 수 있는 수의 범위
vector<bool> visited;

bool dfs (int here)
{
    if(visited[here]) return false;
    visited[here] = true;
    for(int there=minLimit[here]; there<=maxLimit[here]; ++there)
    {
        if(here < minCandidate[there] || maxCandidate[there] < here) continue;
        if(bMatch[there]==-1 || dfs(bMatch[there]))
        {
            aMatch[here] = there;
            bMatch[there] = here;
            return true;
        }
    }
    return false;
}

bool bipartiteMatch ()
{
    aMatch.resize(N+1);
    bMatch.resize(N+1);
    visited.resize(N+1);
    fill(bMatch.begin(), bMatch.end(), -1);
    for(int i=1; i<=N; ++i) // 0번 노드는 미포함
    {
        fill(visited.begin(), visited.end(), false);
        if(!dfs(i)) return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    maxLimit = vector<int>(N+1, N);
    minLimit = vector<int>(N+1, 1);
    maxCandidate = vector<int>(N+1, N);
    minCandidate = vector<int>(N+1, 1);
    for(int i=0; i<M; ++i)
    {
        int flag, start, end, val;
        cin >> flag >> start >> end >> val;       
        switch(flag)
        {
            case 1 : 
                for(int node=start; node<=end; ++node)
                    maxLimit[node] = min(maxLimit[node], val);
                break;
            case 2 :
                for(int node=start; node<=end; ++node)
                    minLimit[node] = max(minLimit[node], val);
                break;
        }

        maxCandidate[val] = min(maxCandidate[val], end);
        minCandidate[val] = max(minCandidate[val], start);
    }
    
    if(bipartiteMatch())
    {
        for(int i=1; i<aMatch.size(); ++i) cout << aMatch[i] << ' ';
        cout << endl;
    }
    else cout << -1 << endl;

    return 0;
}