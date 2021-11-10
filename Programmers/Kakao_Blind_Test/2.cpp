#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;

bool isPrime (ll n)
{
    if(n==1 || n==0) return false;
    int sqrtN = sqrt(n);
    for(int i=2; i<=sqrtN; ++i)
        if(n%i==0) return false;
    return true;
}

int solution(int n, int k) {
    vector<int> baseK;
    while(n!=0)
    {
        int a = n%k;
        baseK.push_back(a);
        n /= k;
    }
    
    reverse(baseK.begin(), baseK.end());
    
    int ans=0;
    ll num = 0;
    for(int i=0; i<baseK.size(); ++i)
    {
        if(baseK[i]==0)
        {
            if(isPrime(num)) ++ans;
            num=0;
            continue;
        }
        else num = num*10 + baseK[i];
    }
    if(isPrime(num)) ++ans;
    return ans;
}