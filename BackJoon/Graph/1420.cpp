#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int MAX_N = 100009, INF = 1000111999, MOD=1000000007;
int sID, eID;
int cache[MAX_N], bCache[MAX_N];
vector<pair<int, int> > dist; //dist, ID
vector<vector<int>> pointG;
vector<set<int>> incomingP;
bool comp (const pair<int, int> & a, const pair<int, int> & b) 
{ return (a.first!=b.first) ? a.first<b.first : a.second<b.second; }

int DP(int hereID, int hereD) // hereD : distance from E
{
    if(hereID == sID) return cache[hereID]=1;
    
    int & ret = cache[hereID];
    if(ret != -1) return ret;
    ret=0;
    //find valut match with pointG[hereID][2](K) in dist
    int k = pointG[hereID][2]+hereD;
    auto iter = lower_bound(dist.begin(), dist.end(), pair{k, -1}, comp);
    for(iter; iter!=dist.end(); ++iter)
    {
        if(iter->first != k) break;
        incomingP[iter-dist.begin()].insert(hereID);
        ret += DP(iter->second, k);
        ret %= MOD;
    }
    return ret % MOD;
}

int backDP(int hereID)
{
    if(hereID == eID) return 1;

    int & ret = bCache[hereID];
    if(ret != -1) return ret;
    ret=0;
    for(auto iter=incomingP[hereID].begin(); iter!=incomingP[hereID].end(); ++iter)
    {
        ret += backDP(*iter);
        ret %= MOD;
    }
    return ret % MOD;
}

void init(int n)
{
    int sX = INF, eX = -INF; 
    for(int i=0; i<n; ++i) //find S, E;
    {
        if(pointG[i][0] < sX)
        {
            sX=pointG[i][0]; sID=i;
        }
        if(pointG[i][0] > eX)
        {
            eX=pointG[i][0]; eID=i;
        }
    }
    dist.resize(n); // calc distance from E
    for(int i=0; i<n; ++i)
    {
        dist[i].first = (pointG[eID][0]-pointG[i][0]) + (pointG[i][1]-pointG[eID][1]); // x-x' + y'-y
        dist[i].second = i; 
    }
    sort(dist.begin(), dist.end());    

    incomingP.resize(n);
    memset(cache, -1, sizeof(cache));
    memset(bCache, -1, sizeof(bCache));
    DP(eID, 0);
    backDP(sID);
}

int recursiveMultply(int a, int b) // guarantee don't make overflow
{
    int res = 0;
    a %= MOD;
    while(b>0)
    {
        if(b%=2 == 1) res = (res+a) % MOD;
        a = (a*2) % MOD;
        b /= 2;
    }
    return res % MOD;
}

vector<int> solution(int n, vector<vector<int>> point, vector<vector<int>> query) 
{
    pointG = point;
    init(n);
    
    vector<int> ans;
    ans.push_back(cache[eID]);
    
    for(int i=0; i<query.size(); ++i)
    {
        int x=query[i][1], y=query[i][2], k=query[i][3];
        if(query[i][0]==0) // insert
        {
            int c = (pointG[eID][0]-x) + (pointG[i][1]-y);
            int outD = k+c, inD = k-c, numOut=0, numIn=0;
            auto iter = lower_bound(dist.begin(), dist.end(), pair{outD, -1}, comp);
            for(iter; iter!=dist.end(); ++iter)
            {
                if(iter->first != outD) break;
                numOut += cache[iter-dist.begin()];
                numOut %= MOD;
            }
            auto iter2 = lower_bound(dist.begin(), dist.end(), pair{inD, -1}, comp);
            for(iter2; iter2!=dist.end(); ++iter2)
            {
                if(iter2->first != inD) break;
                numIn += bCache[iter2-dist.begin()];
                numIn %= MOD;
            }
            numOut = (numOut > 1) ? numOut : 1;
            numIn = (numIn > 1) ? numIn : 1;
            ans.push_back((recursiveMultply(numOut, numIn) + cache[eID]));// % MOD);
        }
        else // delete
        {
            int c = (pointG[eID][0]-x) + (pointG[i][1]-y);
            auto iter = lower_bound(dist.begin(), dist.end(), pair{c, -1}, comp);
            for(iter; iter!=dist.end(); ++iter)
                if(pointG[iter->second][0]==x) break;
            int ID = iter-dist.begin();
            int numOut=cache[ID], numIn=bCache[ID];
             ans.push_back((recursiveMultply(numOut, numIn) - cache[eID] + MOD) % MOD);
        }
    }
    
    return ans;
}