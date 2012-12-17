#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1024
#define MAXM 100000
using namespace std;
struct edge{
    int x, y, d;
    bool same, use, limit;
}e[MAXM];
int n, m, t;
int fa[MAXN];
int father(int x)
{
    if (x != fa[x]) fa[x] = father(fa[x]);
    return fa[x];
}
bool cmp(const edge &a, const edge &b)
{
    return b.d > a.d;
}
void init()
{
    e[0].d = -1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].d);
    for (int i = 1; i <= m; ++i) e[i].same = e[i].use = e[i].limit = false;
    sort(e + 1, e + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
        if ((e[i].d == e[i + 1].d) || (e[i].d == e[i - 1].d)) e[i].same = true;
}
int kruskal(bool change)
{
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int s = 0, cnt = 0;
    for (int i = 1; i <= m; ++i)
    {
        if (e[i].limit) continue;
        fa[e[i].x] = father(e[i].x);
        fa[e[i].y] = father(e[i].y);
        if (fa[e[i].x] != fa[e[i].y]){
            if (change) e[i].use = true;
            s += e[i].d;
            cnt++;
            fa[fa[e[i].x]] = fa[e[i].y];
        }
        if (cnt == n - 1) break;
    }
    if (cnt < n - 1) return -1;
    return s;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        init();
        int min_cost = kruskal(true);
        bool flag = true;
        for (int i = 1; i <= m; ++i)
            if (e[i].same && e[i].use){
                e[i].limit = true;
                if (kruskal(false) == min_cost){
                    flag = false;
                    break;
                }
                e[i].limit = false;
            }
        if (!flag) printf("Not Unique!\n");
        else printf("%d\n", min_cost);
    }
    return 0;
}
