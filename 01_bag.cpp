/*
题目
有N件物品和一个容量为V的背包。第i件物品的费用是v[i]，价值是w[i]。求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。
4 5
1 2
2 4
3 4
4 5

8
*/

/*
二维暴力DP
f(i,j)表示前i个物品，容量为j时的最大价值
f[i][j]=max(f[i-1][j],f[i-1][j-w[i]]+v[i])
时间复杂度为O(n*V)
*/
// #include <iostream>
// #include <algorithm>
// #include <string>
// using namespace std;
// const int N = 1010;
// int v[N], w[N], n, V, dp[N][N];
// int main()
// {
//     cin >> n >> V;
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> v[i] >> w[i];
//     }
//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = 0; j <= V; j++)
//         {
//             dp[i][j] = dp[i - 1][j];
//             if (j >= v[i])
//             {
//                 dp[i][j] = max(dp[i][j], dp[i - 1][j - v[i]] + w[i]);
//             }
//         }
//     }
//     cout << dp[n][V];
//     return 0;
// }

// 滚动数组优化
#include <iostream>
using namespace std;
const int N = 1e3 + 10;
int v[N], w[N], dp[N], n, V;
/*
注：若只将dp[0]赋值为0,其他赋值为-∞,dp[j]表示恰好装满j的最大价值，那么结果需要遍历整个dp
若将整个dp数组赋值为0,dp[j]表示不超过j时候的最大价值，那么结果为dp[V]。


*/
int main()
{
    cin >> n >> V;
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
    cout << dp[V] << endl;
    return 0;
}
