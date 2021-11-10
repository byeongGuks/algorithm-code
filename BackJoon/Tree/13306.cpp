#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int DUMP=123456789;
int numN, numQ;
int parent[200009], edge[200009];

int find(int u)
{
    if(parent[u]==u) return u;
    else parent[u] = find(parent[u]);
    return parent[u];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> numN >> numQ;

    for(int i=2; i<=numN; ++i) cin >> edge[i];
    
    int len = numN + numQ - 1;
    vector<vector<int> > queries (len, vector<int> (3));
    for(int q=0; q<len; ++q)
    {
        int x, c=DUMP, d=DUMP;
        cin >> x;
        switch(x)
        {
            case 0 :
                cin >> c;
                break;
            case 1 :
                cin >> c >> d;
                break;
        }
        queries[q][0]=x; queries[q][1]=c; queries[q][2]=d;
    }

    for(int i=1; i<=numN; ++i) parent[i]=i;

    stack<bool> st;
    for(int q=len-1; q>=0; --q)
    {
        int x=queries[q][0], c=queries[q][1], d=queries[q][2];
        switch(x)
        {
            case 0 :
                parent[c] = edge[c];
                break;
            case 1 :
                if(find(c)==find(d)) st.push(true);
                else st.push(false);
                break;
        }
    }

    while(!st.empty())
    {
        if(st.top()) cout << "YES\n";
        else cout << "NO\n";
        st.pop();
    }
    return 0;
}

