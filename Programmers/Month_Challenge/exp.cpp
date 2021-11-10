#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int changeD(int d, char c)
{
    if(c=='S') return d;
    if(c=='R') return (d+1) % 4;
    return (d+3) % 4;
}

const int INF = 987654321;
int n, m;
const int moveU[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}}; //y,x
vector<vector<vector<bool> > > visited;
bool v [500][500][4];
int destY, destX, destD, ans;
int calcCycle(int y, int x, int d, const vector<string> & grid)
{
    if(v[y][x][d])
    {
        destY=y; destX=x; destD=d;
        return 1;
    }
    if(visited[y][x][d]) return -INF;
    v[y][x][d] = visited[y][x][d] = true;
    int nD = changeD(d, grid[y][x]);
    int nY = y+moveU[nD][0], nX=x+moveU[nD][1];
    nY = (nY+n)%n; nX=(nX+m)%m;

    int ret = calcCycle(nY, nX, nD, grid);
    if(y==destY && x==destX && d==destD) ans = ret;
    return ret+1;
}

vector<int> solution(vector<string> grid) 
{
    vector<int> answer;
    n=grid.size(); m=grid[0].size();
    visited = vector<vector<vector<bool> > >(n, vector<vector<bool>>(m, vector<bool>(4, false)));
    for(int y=0; y<n; ++y)
        for(int x=0; x<m; ++x)
            for(int d=0; d<4; ++d)
            {
                if(visited[y][x][d]) continue;
                memset(v, 0, sizeof(v));
                destY=-1; destX=-1; destD=-1; ans=-1;
                calcCycle(y, x, d, grid);
                if(ans > 0) answer.push_back(ans);
            }
    sort(answer.begin(), answer.end());
    return answer;
}

