/*
完全背包问题：https://www.acwing.com/solution/content/5345/
有 N种物品和一个容量是 V的背包，每种物品都有无限件可用。

第 i种物品的体积是 vi，价值是 wi。

求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
输出最大价值。
4 5
1 2
2 4
3 4
4 5

10
*/
// #include <iostream>
// #include <algorithm >
// #include <string>
// using namespace std;
// const int N = 1e3 + 10;
// int dp[N], v[N], w[N], n, V;
// int main()
// {
//     cin >> n >> V;
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> v[i] >> w[i];
//     }
//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = V; j >= v[i]; j--)
//         {
//             for (int k = 0; k * v[i] <= j; k++)
//             {
//                 dp[j] = max(dp[j], dp[j - k * v[i]] + k * w[i]);
//             }
//         }
//     }
//     cout << dp[V];
//     return 0;
//}

/*
优化：
在第二个循环中，直接由小到大枚举

证明1（很直观）：
f[i , j ] = max( f[i-1,j] , f[i-1,j-v]+w ,  f[i-1,j-2*v]+2*w , f[i-1,j-3*v]+3*w , .....)
f[i , j-v]= max(            f[i-1,j-v]   ,  f[i-1,j-2*v] + w , f[i-1,j-3*v]+2*w , .....)
由上两式，可得出如下递推关系：
                        f[i][j]=max(f[i,j-v]+w , f[i-1][j])

证明2：数学归纳法
对于i=1 显然成立
假设考虑前i-1个物品之后，所有f[j]正确
证明考虑第i个物品后，所有f[j]正确

假设某个j而言，最优解包括k个v[i]
根据第二层循环一定会枚举到f[j-k*v[i]]

f[j-(k-1)*v[i]]会被f[j-k*v[i]]更新
f[j-(k-2)*v[i]]会被f[j-(k-1)*v[i]]更新
...
f[j]会被f[j-v[i]]更新

所以f[j]一定会枚举到最优解,使得f[j]=f[j-k*v[i]]+k*w[i]

*/
#include <iostream>
using namespace std;
const int N = 1e3 + 10;
int dp[N], v[N], w[N], n, V;
int main()
{
    cin >> n >> V;
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i] >> w[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = v[i]; j <= V; j++)
        {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }
    cout << dp[V];
    return 0;
}