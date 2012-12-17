#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#define N 1024
#define M 100000
#define eps 1e-9
#define inf 1e9
using namespace std;
int n, m, s, t, l;
int deg[N], p[N], cur[N], pre[N], dist[N], eid, cnt[N];
double low[N];
struct Edge {
    int u, v;
    double cap, flow;
    int next;
}e[M];
void mapinit() {
    eid = 0;
    memset(p, -1, sizeof(p));
}
void add(int u, int v, double cap, double flow) {
    e[eid].u = u;
    e[eid].v = v;
    e[eid].cap = cap;
    e[eid].flow = flow;
    e[eid].next = p[u];
    p[u] = eid++;
}
void insert(int u, int v, double cap) {
    add(u, v, cap, 0), add(v, u, 0, 0);
}
double isap(int s, int t, int n) {
    int u, v, now;
    double flow = 0;
    memset(dist, 0, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));
    memset(low, 0, sizeof(low));
    for(u = 1; u <= n; u++) cur[u] = p[u];
    u = s;
    while(dist[s] < n) {
        for(now = cur[u]; now != -1; now = e[now].next)
            if(e[now].cap - e[now].flow && dist[u] == dist[v = e[now].v] + 1) break;
        if(now != -1) {
            cur[u] = pre[v] = now;
            low[v] = min(low[u], e[now].cap - e[now].flow);
            u = v;
            if(u == t) {
                for(; u != s; u = e[pre[u]].u) {
                    e[pre[u]].flow += low[t];
                    e[pre[u]^1].flow -= low[t];
                }
                flow += low[t], low[s] = inf;
            }
        } else {
            if(--cnt[dist[u]] == 0) break;
            dist[u] = n, cur[u] = p[u];
            for(now = cur[u]; now != -1; now = e[now].next)
                if(e[now].cap - e[now].flow && dist[u] > dist[v = e[now].v] + 1)
                    dist[u] = dist[v = e[now].v] + 1;
            cnt[dist[u]]++;
            if(u != s) u = e[pre[u]].u;
        }
    }
    return flow;
}
int main()
{
    double x;
    int T, s;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &m, &s);
        mapinit();
        int source = n + m + 1, sink = n + m + 2;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lf", &x);
            insert(source, i, log(x));
        }
        for (int i = 1; i <= m; ++i)
        {
            scanf("%lf", &x);
            insert(i + n , sink, log(x));
        }
        for (int i = 1; i <= s; ++i)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            insert(a, b + n, inf);
        }
        printf("%.4f\n", round(10000.0 * exp(isap(source, sink, sink))) / 10000.0);
    }
    return 0;
}
