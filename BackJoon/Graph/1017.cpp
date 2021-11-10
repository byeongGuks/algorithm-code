#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

vector<vector<int>> graph;
vector<int> matchA, matchB, A, B;
vector<bool> visited;

bool isPrime[2009];
void init()
{
    //memset(isPrime, -1, sizeof(isPrime));
    for(int i=0; i<2009; ++i) isPrime[i]=true;
    isPrime[0]=isPrime[1]=false;
    int sqrtN = sqrt(2009);
    for(int num=2; num<=sqrtN; ++num)
    {
        if(!isPrime[num]) continue;
        for(int mult=num*num; mult<2009; mult+=num) isPrime[mult] = false;
    }
}

bool dfs(int here)
{
    if(visited[here]) return false;
    visited[here] = true;

    for(int there : graph[here])
    {
        if(matchB[there]==-1 || dfs(matchB[there]))
        {
            matchB[there]=here;
            matchA[here]=there;
            return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init();
    int n; cin >> n;
    int tmp; cin >> tmp;
    int flag=tmp%2;
    A.push_back(tmp);
    for(int i=1; i<n; ++i)
    {
        int tmp; cin >> tmp;
        if(tmp%2==flag) A.push_back(tmp);
        else B.push_back(tmp);
    }

    if(A.size() != B.size())
    {
        cout << -1 << endl;
        return 0;
    }

    //make graph
    init(); //Sieve of Eratosthenes
    graph.resize(A.size());
    for(int i=0; i<A.size(); ++i)
    {
        for(int j=0; j<B.size(); ++j)
        {
            if(!isPrime[A[i]+B[j]]) continue;
            graph[i].push_back(j);
        }
    }

    vector<int> ans;
    //biparate matching
    matchA.resize(A.size()); 
    matchB.resize(B.size());
    visited.resize(A.size());
    for(int i=0; i<graph[0].size(); ++i)
    {
        fill(matchA.begin(), matchA.end(), -1);
        fill(matchB.begin(), matchB.end(), -1);
        int there=graph[0][i];
        matchA[0]=there;
        matchB[there]=0;

        int here;
        for(here=1; here<graph.size(); ++here)
        {
            fill(visited.begin(), visited.end(), false);
            visited[0]=true;
            if(!dfs(here)) break;
        }
        if(here==graph.size()) ans.push_back(B[matchA[0]]);
    }
    if(ans.size()) for(int iter : ans) cout << iter <<" ";
    else cout << -1;
    cout << endl;
    return 0;
}