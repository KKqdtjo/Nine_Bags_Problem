#include <iostream>
using namespace std;
const int N = 1e3 + 10;
int v[N], w[N], dp[N], n, V;
int main()
{
    cin >> n >> V;
    for (int i = 1; i <= V; i++)
    {
        dp[i] = -0x3f3f3f3f;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i] >> w[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = V; j >= v[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }
    int res = 0;
    for (int i = 1; i <= V; i++)
    {
        res = max(res, dp[i]);
    }
    cout << res << endl;
    return 0;
}