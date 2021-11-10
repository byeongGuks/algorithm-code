#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int SRC=1*2+1, SINK=2*2; //SRC : 1O SINK 2I 
const int MAX_N = 401*2, INF=987654321;;
int numNode, numEdge;
int capacity[MAX_N][MAX_N], flow[MAX_N][MAX_N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> numNode >> numEdge;  
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    for(int i=1; i<=numNode; ++i) // graph modeling
    {
        int aI=i*2, aO=i*2+1; // 2부터 시작
        capacity[aI][aO] = 1;
    }

    for(int i=0; i<numEdge; ++i)
    {
        int aI, aO, bI, bO;
        cin >> aI >> bI;
        aI=aI*2; aO=aI+1;
        bI=bI*2; bO=bI+1;
        capacity[aO][bI] = 1; //한 간선에 1이상 흐를 수 없음
        capacity[bO][aI] = 1;
    }

    int ans = 0;
    int graphSize = (numNode+1) * 2;
    vector<int> parent(graphSize);
    while(true)
    {
        queue<int> que;
        que.push(SRC);
        fill(parent.begin(), parent.end(), -1);
        parent[SRC] = SRC;
        while(!que.empty())
        {
            int here = que.front(); que.pop();
            for(int there=3; there<graphSize; ++there)
            {
                int r = capacity[here][there]-flow[here][there];
                if(r<=0 || parent[there]!=-1) continue;
                que.push(there);
                parent[there] = here;
            }
        }
        if(parent[SINK]==-1) break;

        for(int here=SINK; here!=SRC; here=parent[here])
        {
            flow[here][parent[here]] += -1;
            flow[parent[here]][here] += 1;
        }
        ans += 1;
    }
    cout << ans << endl;
}

