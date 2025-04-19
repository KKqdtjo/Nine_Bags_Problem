/*
有依赖的背包问题

有 N个物品和一个容量是 V的背包。
物品之间具有依赖关系，且依赖关系组成一棵树的形状。如果选择一个物品，则必须选择它的父节点。
每件物品的编号是 i，体积是 vi，价值是 wi，依赖的父节点编号是 pi。物品的下标范围是 1…N。

输入格式
第一行有两个整数 N，V，用空格隔开，分别表示物品个数和背包容量。

接下来有 N行数据，每行数据表示一个物品。
第 i行有三个整数 vi,wi,pi，用空格隔开，分别表示物品的体积、价值和依赖的物品编号。
如果 pi=−1，表示根节点。 数据保证所有物品构成一棵树。

数据范围
1≤N,V≤100
1≤vi,wi≤100
父节点编号范围：
内部结点：1≤pi≤N;
根节点 pi=−1;

5 7
2 3 -1
2 2 1
3 5 1
4 7 2
3 6 2

11
*/
/*
有依赖的背包问题：
1. 物品之间有依赖关系，构成一棵树
2. 选择一个物品必须选择其父节点
3. 求解在不超过背包容量的情况下，能获得的最大价值

算法思路：
1. 状态表示：dp[i][j]表示以i为根的子树中，容量为j的背包能获得的最大价值
2. 状态转移：
   - 先处理当前节点：dp[x][i] = w[x]（i >= v[x]）
   - 再处理子节点：dp[x][j] = max(dp[x][j], dp[x][j-k] + dp[y][k])
     其中y是x的子节点，k是分配给y子树的容量
3. 使用DFS遍历树，自底向上计算dp值

时间复杂度：O(N * V^2)，其中N是物品数量，V是背包容量
空间复杂度：O(N * V)
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 110;
int dp[N][N], n, V, root, v[N], w[N];
vector<int> g[N];
void dfs(int x)
{
    for (int i = v[x]; i <= V; i++)
    {
        dp[x][i] = w[x];
    }
    for (int i = 0; i < g[x].size(); i++)
    {
        int y = g[x][i];
        dfs(y);
        for (int j = V; j >= v[x]; j--)
        {
            for (int k = 0; k <= j - v[x]; k++)
            {
                dp[x][j] = max(dp[x][j], dp[x][j - k] + dp[y][k]);
            }
        }
    }
}
int main()
{
    cin >> n >> V;
    for (int i = 1; i <= n; i++)
    {
        int fa;
        cin >> v[i] >> w[i] >> fa;
        if (fa == -1)
        {
            root = i;
        }
        else
        {
            g[fa].push_back(i);
        }
    }
    dfs(root);
    cout << dp[root][V] << endl;
    return 0;
}