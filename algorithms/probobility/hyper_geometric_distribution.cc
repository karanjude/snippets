#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

long long choose[41][41];
int C;
int N;
double solved[41];

double Solve(int k)
{
    if (solved[k] != -1)
        return solved[k];

    double factor = 1.0/(1.0-(double)choose[C-k][N]/choose[C][N]);
    double ans = 1;
    int minVal = min(k,N);
    for (int j = 1; j <= minVal; j++)
    {
        if (k - j == 0) continue;
        double p = (double)(choose[k][j] * choose[C - k][N - j]) / choose[C][N];
        if (p != 0)
            ans += p*Solve(k - j);
    }
    ans *= factor;
    solved[k] = ans;
    return ans;
}

int main(int argc,char** argv)
{
    string basePath = "";
    string inFile = basePath + "large.txt";
    string outFile = basePath + "output.txt";

    freopen(inFile.c_str(),"r",stdin);
    freopen(outFile.c_str(),"w",stdout);

    for (int i=0; i<41; i++)
    {
        choose[i][i] = 1;
        choose[i][0] = 1;
        for (int j=1; j<i; j++)
            choose[i][j] = choose[i-1][j] + choose[i-1][j-1];
    }

    int testCases; cin >> testCases;
    for (int caseNo = 1; caseNo <= testCases; caseNo++)
    {
        cin >> C >> N;
        for(int i=0; i<41;i++)
            solved[i]=-1;

        cout << "Case #" << caseNo << ": " << Solve(C) << endl;
    }
}
