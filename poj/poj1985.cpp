#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#define N 100010
#define M 1000010
using namespace std;
struct edge
{
    int v, d, next;
}e[M];
int p[N], eid;
void mapinit()
{
    memset(p, -1, sizeof(p));
    eid = 0;
}
void insert(int x, int y, int d)
{
    e[eid].v = y;
    e[eid].d = d;
    e[eid].next = p[x];
    p[x] = eid++;
}
void insert2(int x, int y, int d)
{
    insert(x, y, d);
    insert(y, x, d);
}
int n, m;
//�ñ߱�洢
bool inq[N], vst[N];
int cnt[N];
int d[N];//��v��i�����·����
bool spfa(int v)//�и�������true,���򷵻�false
{
    memset(cnt, 0, sizeof(cnt));
    memset(inq, false, sizeof(inq));
    memset(d, 0, sizeof(d));
    cnt[v] = 1;
    inq[v] = true;
    queue<int> q;
    q.push(v);
    d[v] = 0;
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        vst[x] = true;
        for (int i = p[x]; i != -1; i = e[i].next)
            if ((d[x] + e[i].d > d[e[i].v]) && !inq[e[i].v])
            {
                d[e[i].v] = d[x] + e[i].d;
                q.push(e[i].v);
                inq[e[i].v] = true;
            }
    }
    return false;//�޸�������false
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        mapinit();
        for (int i = 1; i <= m; ++i)
        {
            int x, y, d; char c;
            scanf("%d%d%d %c", &x, &y, &d, &c);
            insert2(x, y, d);
        }
        spfa(1);
        int st = 1;
        for (int i = 1; i <= n; ++i)
            if (d[i] > d[st]) st = i;
        spfa(st);
        int res = 0;
        for (int i = 1; i <= n; ++i) res = max(res, d[i]);
        printf("%d\n", res);
    }
    return 0;
}
