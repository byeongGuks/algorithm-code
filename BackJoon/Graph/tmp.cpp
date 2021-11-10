#include <string>
#include <vector>
#include <set>

using namespace std;

const int INF = 987654321;
int pow2[30];
int fill2[30];
void init()
{
    int a=1;
    for(int i=0; i<30; ++i)
    {
        pow2[i]=a;
        a*=2;
    }

    fill2[0] = 0;
    for(int i=0; i<30; ++i)
    {
        fill2[i] = fill2[i-1] + pow2[i];
    }
}

int findFirst1(int num)
{
    int pos=-1;
    for(int i=0; i<30; ++i)
    {
        if(num%2==1) pos=i;
        num/=2;
    }
    return pos;
}

vector<int> solution(vector<int> m, vector<int> b) {
    vector<int> ans;
    init();
    int start = 0, end=0;
    for(int i=0; i<m.size(); ++i)
    {
        int ret=0;
        end += m[i];
        vector<int> s;
        for(int j=start; j<end; ++j) s.push_back(b[j]);
        while(true)
        {
            int a=s[0];
            for(int iter : s) a = a & iter;
            if(a==0) break;
            int pos = findFirst1(a);
            for(int & iter : s) iter = iter & fill2[pos];

            int minElem=INF, minElemID;
            for(int i=0; i<s.size(); ++i)
                if(s[i] < minElem)
                {
                    minElem = s[i];
                    minElemID = i;
                }
            ret += minElem+1;
            s[minElemID] = fill2[pos];
        }
        ans.push_back(ret);
        start = end;
    }
    return ans;
}