#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 987654321;

int cache[11][11];
int DP(int pos, int n, const vector<int> & info)
{
    if(pos==11) return 0;
    
    int & ret = cache[pos][n];
    if(ret != -1) return ret;
    
    ret = DP(pos+1, n, info); // 해당 과녁은 안 맞추기로 결정
    if(n > info[pos]) 
    {
        int a = DP(pos+1, n-info[pos]-1, info) + pos;
        if(info[pos]!=0) a+=pos;
        ret = max(ret, a);
    }
    return ret;
}

int cache2[11][11];
int findMaxN(int pos, int n, const vector<int> & info)
{
    if(pos==11) return n;
    
    int & ret = cache2[pos][n];
    if(ret != -1) return ret;
    
    if(n > info[pos])
    {
        int tmp = (info[pos]==0) ? pos : pos*2;
        if(cache[pos][n] == cache[pos+1][n-info[pos]-1] + tmp)
            ret = findMaxN(pos+1, n-info[pos]-1, info);
    }
    if(cache[pos][n] == cache[pos+1][n])
        ret = max(ret, findMaxN(pos+1, n, info));
    return ret;
}

vector<int> path; // 역순으로 저장됨
void backTracking(int pos, int n, const vector<int> & info)
{
    if(pos==11) return;
    
    if(n > info[pos])
    {
        int tmp = (info[pos]==0) ? pos : pos*2;
        if(cache[pos][n] == cache[pos+1][n-info[pos]-1] + tmp)
        {
            path.push_back(info[pos]+1);
            backTracking(pos+1, n-info[pos]-1, info);
            return;
        } 
    }
    
    path.push_back(0);
    backTracking(pos+1, n, info);
}

vector<int> solution(int n, vector<int> info)
{
    int apeachPoint = 0;
    reverse(info.begin(), info.end());
    for(int i=0; i<=10; ++i)
        if(info[i]!=0) apeachPoint += i;
    
    memset(cache, -1, sizeof(cache));
    for(int i=1; i<=n; ++i) DP(1, i, info);
    if(cache[1][n] <= apeachPoint) return {-1};
    
    memset(cache2, -1, sizeof(cache2));
    int numZero = findMaxN(1, n, info);
    
    path.clear();
    backTracking(1, n-numZero, info);
    reverse(path.begin(), path.end());
    path.push_back(numZero);
    return path;
}

