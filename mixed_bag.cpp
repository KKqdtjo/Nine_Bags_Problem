/*
混合背包问题
有N种物品和一个容量是V的背包。
物品一共有三类：
第一类物品只能用1次（01背包）；
第二类物品可以用无限次（完全背包）；
第三类物品最多只能用 si次（多重背包）；

每种体积是 vi，价值是 wi。 

si=−1表示第 i种物品只能用1次；
si=0表示第 i种物品可以用无限次；
si>0表示第 i种物品可以使用 si次；

求解将哪些物品装入背包，可使物品体积总和不超过背包容量，且价值总和最大。
输出最大价值。

0<N,V≤1000
0<vi,wi≤1000
−1≤si≤1000

4 5
1 2 -1
2 4 1
3 4 0
4 5 2

8
*/

/*
大致思路: 多重背包可用二进制优化转换为01背包，01背包和完全背包唯一不同的地方在于第二层循环顺序
但是共同点在于每循环一次，必然使得当前i下的f[j]最优
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1e3 + 10;
int n, V, dp[N];
struct Good
{
    int kind;
    int v, w;
};
vector<Good> goods;
int main()
{
    cin >> n >> V;
    for (int i = 0; i < n; i++)
    {
        int v, w, s;
        cin >> v >> w >> s;
        if (s == -1)
        {
            goods.push_back({0, v, w});
        }
        else if (s == 0)
        {
            goods.push_back({-1, v, w});
        }
        else
        {
            for (int j = 1; j <= s; j *= 2)
            {
                s -= j;
                goods.push_back({0, j * v, j * w});
            }
            if (s)
            {
                goods.push_back({0, s * v, s * w});
            }
        }
    }
    for (auto good : goods)
    {
        if (!good.kind)
        {
            for (int j = V; j >= good.v; j--)
            {
                dp[j] = max(dp[j], dp[j - good.v] + good.w);
            }
        }
        else
        {
            for (int j = good.v; j <= V; j++)
            {
                dp[j] = max(dp[j], dp[j - good.v] + good.w);
            }
        }
    }
    cout << dp[V];
    return 0;
}
