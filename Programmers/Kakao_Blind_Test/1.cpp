#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) 
{
    int n = id_list.size();
    map<string, int> id;
    vector<set<int> > s(n);
    vector<int> cnt(n, 0), ans(n, 0);

    for(int i=0; i<id_list.size(); ++i) id.insert({id_list[i], i});
    
    for(string & iter : report)
    {
        int idx=0;
        while(iter[idx]!=' ') ++idx;
        string a = iter.substr(0, idx);
        string b = iter.substr(idx+1, iter.size()-idx-1);
        int aID = id.find(a)->second, bID = id.find(b)->second;
        if(s[bID].find(aID) == s[bID].end())
        {
            s[bID].insert(aID);
            ++cnt[bID];
        }
    }
    
    for(int i=0; i<n; ++i)
    {
        if(cnt[i] < k) continue;
        for(auto iter=s[i].begin(); iter!=s[i].end(); ++iter)
            ++ans[*iter];
    }
    
    return ans;
}