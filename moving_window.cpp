#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;

const int N = 1000010;
int a[N];
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i]; 
    deque<int> q;
    for (int i = 1; i <= n; i++)
    {
        while (q.size() && q.back() > a[i]) // 新进入窗口的值小于队尾元素，则队尾出队列
            q.pop_back();
        q.push_back(a[i]);                       // 将新进入的元素入队
        if (i - k >= 1 && q.front() == a[i - k]) // 若队头是否滑出了窗口，队头出队
            q.pop_front();
            
        if (i >= k) // 当窗口形成，输出队头对应的值
            cout << q.front() << " ";
    }
    q.clear();
    cout << endl;

    // 最大值亦然
    for (int i = 1; i <= n; i++)
    {
        while (q.size() && q.back() < a[i])
            q.pop_back();
        q.push_back(a[i]);
        if (i - k >= 1 && a[i - k] == q.front())
            q.pop_front();
        if (i >= k)
            cout << q.front() << " ";
    }
}
