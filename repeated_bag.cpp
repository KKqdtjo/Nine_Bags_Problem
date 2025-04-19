/*
多重背包：
有 N种物品和一个容量是 V的背包。
第 i种物品最多有 si件，每件体积是 vi，价值是 wi。
求解将哪些物品装入背包，可使物品体积总和不超过背包容量，且价值总和最大。
输出最大价值。
v1:
0<N,V≤100
0<vi,wi,si≤100

v2:
0<N≤1000
0<V≤2000
0<vi,wi,si≤2000

v3:   https://www.acwing.com/solution/content/53507/
0<N≤1000
0<V≤20000
0<vi,wi,si≤20000

4 5
1 2 3
2 4 1
3 4 3
4 5 2

10
*/

// v1:暴力DP
// O(N*V*S)

// #include <iostream>
// using namespace std;
// const int N = 1e3 + 10;
// int v[N], w[N], s[N], dp[N], n, V;
// int main()
// {
//     cin >> n >> V;
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> v[i] >> w[i] >> s[i];
//     }
//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = V; j >= v[i]; j--)
//         {
//             for (int k = 1; k <= s[i] && k * v[i] <= j; k++)
//             {
//                 dp[j] = max(dp[j], dp[j - k * v[i]] + k * w[i]);
//             }
//         }
//     }
//     cout << dp[V];
//     return 0;
// }

// v2:二进制优化
// #include <iostream>
// #include <vector>
// using namespace std;
// const int N = 2010;
// int dp[N], n, V;
// struct Good
// {
//     int w, v;
// };
// int main()
// {
//     vector<Good> goods;
//     cin >> n >> V;
//     for (int i = 1; i <= n; i++)
//     {
//         int v, w, s;
//         cin >> v >> w >> s;
//         for (int j = 1; j <= s; j *= 2)
//         {
//             goods.push_back({w * j, v * j});
//             s -= j;
//         }
//         if (s)
//         {
//             goods.push_back({w * s, v * s});
//         }
//     }
//     //大概运行次数：1000*log(2000)*2000
//     for (auto good : goods)
//     {
//         for (int j = V; j >= good.v; j--)
//         {
//             dp[j] = max(dp[j], dp[j - good.v] + good.w);
//         }
//     }
//     cout << dp[V];
//     return 0;
// }

// v3: 单调队列：https://www.acwing.com/solution/content/53507/
// 朴素版
// #include <iostream>
// #include <deque>
// #include <algorithm>
// using namespace std;
// const int N = 2e4 + 10;
// const int M = 1e3 + 10;
// int n, V;
// int f[M][N];
// int v[M], w[M], s[M];
// int main()
// {
//     cin >> n >> V;
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> v[i] >> w[i] >> s[i];
//     }

//     for (int i = 1; i <= n; i++)
//     {
//         for (int r = 0; r < v[i]; r++)
//         {
//             deque<int> q;
//             for (int j = r; j <= V; j += v[i])
//             {
//                 while (q.size() && j - q.front() > s[i] * v[i])
//                 {
//                     q.pop_front();
//                 }
//                 while (q.size() && f[i - 1][q.back()] + (j - q.back()) / v[i] * w[i] <= f[i - 1][j])
//                 {
//                     q.pop_back();
//                 }
//                 q.push_back(j);

//                 f[i][j] = f[i - 1][q.front()] + (j - q.front()) / v[i] * w[i];
//             }
//         }
//     }
//     cout << f[n][V] << endl;
//     return 0;
// }

// 由于deque的高常数开销，模拟队列性能更好
// 二维朴素版
/*
时间复杂度：O(n×v)
空间复杂度：O(n×v)
滑动窗口的长度为 si+1
*/
// #include <iostream>
// using namespace std;
// const int N = 1e3 + 10;
// const int M = 2e4 + 10;
// int v[N], w[N], s[N], n, V, f[N][M], q[M];
// int main()
// {
//     scanf("%d%d", &n, &V);
//     for (int i = 1; i <= n; i++)
//     {
//         scanf("%d%d%d", v + i, w + i, s + i);
//     }
//     for (int i = 1; i <= n; i++)
//     {
//         for (int r = 0; r < v[i]; r++)
//         {
//             int hh = 0, tt = -1;
//             for (int j = r; j <= V; j += v[i])
//             {
//                 while (hh <= tt && f[i - 1][q[tt]] + (j - q[tt]) / v[i] * w[i] < f[i - 1][j])
//                 {
//                     tt--;
//                 }
//                 q[++tt] = j;
//                 while (hh <= tt && j - q[hh] > v[i] * s[i])
//                 {
//                     hh++;
//                 }
//                 f[i][j] = f[i - 1][q[hh]] + (j - q[hh]) / v[i] * w[i];
//             }
//         }
//     }
//     cout << f[n][V] << endl;
//     return 0;
// }
// 一维优化：拷贝数组
/*
时间复杂度：O(n×v)
空间复杂度：O(v)
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e3 + 10;
const int M = 2e4 + 10;
int v[N], w[N], s[N], dp[M], g[M], n, V, q[M];
int main()
{
    cin >> n >> V;
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i] >> w[i] >> s[i];
    }
    for (int i = 1; i <= n; i++)
    {
        memcpy(g, dp, sizeof(dp));
        for (int r = 0; r < v[i]; r++)
        {
            int hh = 0, tt = -1;
            for (int j = r; j <= V; j += v[i])
            {
                while (tt >= hh && g[q[tt]] + (j - q[tt]) / v[i] * w[i] <= g[j])
                {
                    tt--;
                }
                q[++tt] = j;
                while (tt >= hh && j - q[hh] > s[i] * v[i])
                {
                    hh++;
                }
                dp[j] = g[q[hh]] + (j - q[hh]) / v[i] * w[i];
            }
        }
    }
    cout << dp[V] << endl;
    return 0;
}
/*
滚动数组写法：
#include <iostream>

using namespace std;

const int N = 1010, M = 20010;

int n, m;
int v[N], w[N], s[N];
int f[2][M];// 仅保留当前层和上一层，(i - 1) & 1 表示上一层状态，通过位运算 & 1 交替使用数组空间
int q[M];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> v[i] >> w[i] >> s[i];
    for (int i = 1; i <= n; ++ i)
    {
        for (int r = 0; r < v[i]; ++ r)
        {
            int hh = 0, tt = -1;
            for (int j = r; j <= m; j += v[i])
            {
                while (hh <= tt && j - q[hh] > s[i] * v[i]) hh ++ ;
                while (hh <= tt && f[(i - 1) & 1][q[tt]] + (j - q[tt]) / v[i] * w[i] <= f[(i - 1) & 1][j]) -- tt;
                q[ ++ tt] = j;
                f[i & 1][j] = f[(i - 1) & 1][q[hh]] + (j - q[hh]) / v[i] * w[i];
            }
        }
    }
    cout << f[n & 1][m] << endl;
    return 0;
}





*/
