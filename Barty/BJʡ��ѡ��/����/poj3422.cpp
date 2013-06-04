#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define INF 1000000000
#define MAXN 10000
#define MAXM 10485760
using namespace std;
struct edge{
    int x, y, f, c, next;
}e[MAXM];
int eid, p[MAXN];//�ڽӱ����ݽṹ
int n, m, source, sink;//source���Դ�㣬sink��ǻ��
int d[MAXN], pre[MAXN], path[MAXN];//pre������·���Ͻڵ��ǰ����path��¼������������չ������
queue<int> q;//SPFAʹ�õĶ���
bool use[MAXN];//����Ƿ��ڶ�����
void insert(int x, int y, int f, int c)
{
    e[eid].x = x;
    e[eid].y = y;
    e[eid].f = f;
    e[eid].c = c;
    e[eid].next = p[x];
    p[x] = eid++;
}
void insert1(int x, int y, int f, int c)
{
    insert(x, y, f, c);
    insert(y, x, 0, -c);
}
void insert2(int x, int y, int f, int c)
{
    insert1(x, y, f, c);
    insert1(y, x, f, c);
}
void mapinit()
{
    memset(p, -1, sizeof(p));
    eid = 0;
}
void print_map()
{
    for (int i = 1; i <= n; ++i)
    {
        printf("%d:", i);
        for (int j = p[i]; j != -1; j = e[j].next)
            printf("(%d,%d,%d) ", e[j].y, e[j].f, e[j].c);
        printf("\n");
    }
}
bool spfa(int s)
{
    memset(use, false, sizeof(use));
    int u, v;
    for (int i = 1; i <= n; ++i) d[i] = INF;
    while (!q.empty()) q.pop();
    q.push(s);
    d[s] = 0;
    pre[s] = -1;
    use[s] = true;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for (int i = p[u]; i != -1; i = e[i].next)
        {
            v = e[i].y;
            if ((e[i].f != 0) && (d[u] + e[i].c < d[v])){
                d[v] = d[u] + e[i].c;
                pre[v] = u;
                path[v] = i;
                if (!use[v]){
                    use[v] = true;
                    q.push(v);
                }
            }
        }
        use[u] = false;
    }
    return (d[sink] != INF);
}
int argument()
{
    int delta = INF, res = 0;
    for (int i = sink; pre[i] != -1; i = pre[i])
        delta = min(delta, e[path[i]].f);
    for (int i = sink; pre[i] != -1; i = pre[i])
    {
        e[path[i]].f -= delta;
        e[path[i] ^ 1].f += delta;
        res += e[path[i]].c * delta;
    }
    return res;
}
int maxcostflow()
{
    int sum = 0;
    while (spfa(source)) sum += argument();
    return sum;
}
int num[64][64], step[2][2] = {{1, 0}, {0, 1}};
int ord(int x, int y, int c)
{
    return c * n * n + (x - 1) * n + y;
}
int inside(int x)
{
    return (x >= 1) && (x <= n);
}
bool init()
{
    mapinit();
    if (scanf("%d%d", &n, &m) == EOF) return false;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &num[i][j]);
            insert1(ord(i, j, 0), ord(i, j, 1), 1, -num[i][j]);
        }
    source = n * n * 2 + 1, sink = n * n * 2 + 2;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 0; k < 2; ++k)
            {
                int dx = i + step[k][0], dy = j + step[k][1];
                if (inside(dx) && inside(dy)){
                    for (int c = 0; c < 4; ++c)
                        insert1(ord(i, j, (c & 2) >> 1), ord(dx, dy, c & 1), INF, 0);
                }
            }
    insert1(source, 1, m, 0);
    insert1(n * n * 2, sink, m, 0);
    n = sink;
//    print_map();
    return true;
}
int main()
{
    while (init())
        printf("%d\n", -maxcostflow());
    return 0;
}
