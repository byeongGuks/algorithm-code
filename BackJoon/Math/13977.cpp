// endl 대신에 \n 쓰기
// 이거 때매 열번 틀림 ㅋㅋ
#include <iostream>

using namespace std;
typedef long long ll;
const ll MOD = 1e9+7, MAX_NUM=4000001;
ll nFact [MAX_NUM], kFactPow[MAX_NUM]; // k!^(MOD-2)

ll powU (ll a, ll b) // a^b % MOD
{
    ll ret = 1;
    while(b)
    {
        if(b & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ret;
}

void init(){
	nFact[0] = 1;
	for(int i=1; i<=4000000; i++) nFact[i] = nFact[i - 1] * i % MOD;
	kFactPow[4000000] = powU(nFact[4000000], MOD-2);
	for(int i=3999999; i>=0; i--){
		kFactPow[i] = kFactPow[i+1] * (i + 1) % MOD;
	}
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int numCase;
    cin >> numCase;
    init(); 
    while(numCase--)
    {
       int n, k;
       cin >> n >> k;
       ll ret = nFact[n];
       ret = ret * kFactPow[k] % MOD;
       ret = ret * kFactPow[n-k] % MOD;
       cout << ret << "\n";
    }
    return 0;
}

