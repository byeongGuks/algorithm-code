
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

const int MAX_N = 401;
const int INF = 987654321;
int numNode, numEdge;
int capacity[MAX_N][MAX_N], flow[MAX_N][MAX_N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	memset(capacity, 0, sizeof(capacity));
	memset(flow, 0, sizeof(flow));

	cin >> numNode >> numEdge;
	for(int i=0; i<numEdge; ++i)
	{
		int a, b;
		cin >> a >> b;
		++capacity[a][b];
	}

	int totalFlow = 0;
	vector<int> parent(numNode+1);
	while(true)
	{
		//bfs로 경로 찾기
		fill(parent.begin(), parent.end(), -1);
		parent[1] = 1;
		queue<int> que;
		que.push(1);

		while(!que.empty())
		{
			int here = que.front();
			que.pop();
			for(int next=1; next<MAX_N; ++next)
			{
				int r = capacity[here][next] - flow[here][next];
				if(r<=0 || parent[next]!=-1) continue; // r==0
				parent[next] = here;
				que.push(next);
			}
		}

		if(parent[2]==-1) break;

		int amount = INF;
		for(int p=2; p!=1; p=parent[p])
			amount = min(amount, capacity[parent[p]][p]-flow[parent[p]][p]);
		
		for(int p=2; p!=1; p=parent[p])
		{
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}

		totalFlow += amount;
	}
	cout << totalFlow << endl;

	return 0;
}
