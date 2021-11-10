#include <iostream>

using namespace std;

const int nofill[4][2] = {
    {1, 1}, {0, 1}, {0, 0}, {0, 1}
};
const int pow2[8] = {1, 2, 4, 8, 16, 32, 64, 128};

int k, tX, tY;
int board[129][129];
int blockID;

void fillFull(int x, int y, int k, int id)
{
    int cX=x+pow2[k-1], cY=y+pow2[k-1], a=noFill[id][0], b=noFill[id][1];

    for(int i=0; i<2; ++i)
        for(int j=0; j<2; ++j)
        {
            if(i==a && j==b) continue;
            board[cX+i][cY+j] == blockID;
        }
    ++blockID;

}

void fiilBoard(int x, int y, int k)
{
    int a=0,b=0, cX=x+pow2[k-1], cY=y+pow2[k-1];
    if(cX >= tX) a=1;
    if(cY >= tY) b=1;

    for(int i=0; i<2; ++i)
        for(int j=0; j<2; ++j)
        {
            if(i==a && j==b) continue;
            board[cX+i][cY+j] == blockID;
        }
    ++blockID;
}

void solve()
{
    blockID = 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> k >> tX >> tY;

    return 0;
}

