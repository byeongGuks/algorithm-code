#include <string>
#include <vector>
#include <set>

using namespace std;
 
int ans;
vector<vector<int> > graph;
vector<int> gInfo;

void bf(int a, int b, set<int> visited)
{
    if(a==b) 
    {
        ans = max(a, ans);
        return;
    }    
    
    int size = 0;
    while(visited.size() != size)
    {
        size = visited.size();
        for(int iter : visited)
            for(int i=0; i<graph[iter].size(); ++i)
            {
                int there=graph[iter][i];
                if(gInfo[there]==0 && visited.find(there)==visited.end())
                {
                    visited.insert(there);
                    ++a;
                }    
            }
    }
    if(visited.size() == g.info.size())
    {
        ans = max(ans, a);
        return;
    }
    for(int iter : visited)
        for(int i=0; i<graph[iter].size(); ++i)
        {
            int there=graph[iter][i];
            if(visited.find(there)==visited.end())
            {
                visited.insert(there);
                bf(a, b+1, visited);
                visited.erase(there);
            } 
        }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    graph.resize(info.size());
    for(auto & iter : edges)
        graph[iter[0]].push_back(iter[1]);
    gInfo = info;
    
    int a=1, b=0; //양 늑대
    set<int> visited; visited.insert(0);
    ans = 1;
    bf(a, b, visited);
    return ans;
}