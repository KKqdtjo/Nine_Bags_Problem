/*
二维费用的背包问题

有 N件物品和一个容量是 V的背包，背包能承受的最大重量是 M。

每件物品只能用一次。体积是 vi，重量是 mi，价值是 wi。

求解将哪些物品装入背包，可使物品总体积不超过背包容量，总重量不超过背包可承受的最大重量，且价值总和最大。
输出最大价值。

数据范围
0<N≤1000
0<V,M≤100
0<vi,mi≤100
0<wi≤1000

4 5 6
1 2 3
2 4 4
3 4 5
4 5 6

8
*/
#include <iostream>
using namespace std;
const int N = 110;
int dp[N][N];
int n, V, M;
int main()
{
    cin >> n >> V >> M;
    for (int i = 0; i < n; i++)
    {
        int v, m, w;
        cin >> v >> m >> w;
        for (int j = V; j >= v; j--)
        {
            for (int k = M; k >= m; k--)
            {
                dp[j][k] = max(dp[j][k], dp[j - v][k - m] + w);
            }
        }
    }
    cout << dp[V][M];
    return 0;
}