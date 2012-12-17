#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#define LL long long
#define MAXN 100010
using namespace std;
LL num[MAXN], a[MAXN], b[MAXN];
int n;
LL get_ans()
{
    for (int i = 1; i <= n; ++i) { a[i] = i; b[i] = i; }
    num[0] = num[n + 1] = -INT_MAX;
    a[0] = b[n + 1] = -1;
    for (int i = 1; i <= n; ++i)
        while (num[a[i] - 1] >= num[i]) a[i] = a[a[i] - 1];
    for (int i = n; i >= 1; --i)
        while (num[b[i] + 1] >= num[i]) b[i] = b[b[i] + 1];
    LL now_max = 0;
    for (int i = 1; i <= n; ++i)
        now_max = max(now_max, (b[i] - a[i] + 1) * num[i]);
    return now_max;
}
int main()
{
    LL x;
    while (scanf("%d", &n), n)
    {
        memset(num, 0, sizeof(num));
        for (int i = 1; i <= n; ++i)
            scanf("%d", &num[i]);
        printf("%lld\n", get_ans());
    }
    return 0;
}
