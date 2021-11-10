#include <string>
#include <vector>
#include <map>

using namespace std;

const long long MAX = 1e15+9;
typedef long long ll;

ll min (ll a, ll b)
{
    if(a<b) return a;
    else return b;
}

ll max (ll a, ll b)
{
    if(a>b) return a;
    else return b;
}

ll f (ll v, ll w, ll t, ll time)
{
    ll cnt = (time / (2*t)) + (time % (2*t) >= t ? 1 : 0);
    return min(v, cnt*w);
}

long long solve (ll target, const vector<ll> & val, const vector<ll> & w, const vector<ll> & t)
{
    ll s=1, e=MAX;
    
    while(s!=e)
    {
        ll mid = (s+e)/2;
        ll sum=0;
        for(int i=0; i<val.size(); ++i) sum+=f(val[i], w[i], t[i], mid);
        if(sum < target) s = mid+1;
        else e = mid;
    }
    return s;
}

long long solution(int a, int b, vector<int> g, vector<int> s, vector<int> w, vector<int> t) {
    long long answer = -1;

    int n = g.size();
    vector<ll> vv(n), gg(n), ss(n), ww(n), tt(n);
    for(int i=0; i<n; ++i)
    {
        gg[i]=g[i]; ss[i]=s[i]; ww[i]=w[i]; tt[i]=t[i];
        vv[i]=gg[i]+ss[i];
    }
    ll ta = solve(a, gg, ww, tt);
    ll tb = solve(b, ss, ww, tt);
    ll tc = solve(a+b, vv, ww, tt);
    
    answer = max(ta, max(tb, tc));
    return answer;
}