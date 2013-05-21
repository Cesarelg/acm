#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 512
int n;
int x[N], y[N];
bool mat[N + 1][N + 1];
bool inque[N + 1];
int que[N], head, tail;
int match[N + 1], father[N + 1], base[N + 1];
int inpath[N + 1];
int pcnt = 0;               // count of paths have existed
int inblossom[N + 1];
int bcnt = 0;               // count of blossoms have existed
void mapinit()
{
    bcnt = pcnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        match[i] = 0;
        for (int j = 1; j <= n; ++j)
            mat[i][j] = false;
    }
}
int pop() { return que[head++]; }
void push(int x)
{
    que[tail++] = x;
    inque[x] = true;
}
void insert1(int a, int b)
{
    mat[a][b] = true;
}
void insert2(int a, int b)
{
    mat[a][b] = mat[b][a] = true;
}
int find_ancestor(int u, int v)
{
    ++pcnt;
    while (u)
    {
        u = base[u];
        inpath[u] = pcnt;
        u = father[match[u]];
        // if match[u] == 0, meaning u is the root node, it also works, because father[0] == 0
    }
    while (true)
    {
        v = base[v];
        if (inpath[v] == pcnt) return v;
        v = father[match[v]];
    }
}
void reset(int u, int anc)
{
    while (u != anc)
    {
        int v = match[u];
        inblossom[base[v]] = bcnt;
        inblossom[base[u]] = bcnt;
        v = father[v];
        if (base[v] != anc) father[v] = match[u];
        u = v;
    }
}
void contract(int u, int v)
{
    int anc = find_ancestor(u, v);
    ++bcnt;
    reset(u, anc);
    reset(v, anc);
    if (base[u] != anc) father[u] = v;
    if (base[v] != anc) father[v] = u;
    for (int i = 1; i <= n; ++i)
        if (inblossom[base[i]] == bcnt)
        {
            base[i] = anc;
            if (!inque[i]) push(i);
        }
}
int find_augment(int start)
{
    for (int i = 1; i <= n; ++i)
    {
        father[i] = 0;
        inque[i] = false;
        base[i] = i;
    }
    head = 0; tail = 0; push(start);
    while (head < tail)
    {
        int u = pop();
        for (int v = 1; v <= n; ++v)
            if (mat[u][v] && base[v] != base[u] && match[v] != u) {
                if (v == start || (match[v] && father[match[v]]))
                // node v is out-point
                contract(u, v);               // make blossom
                else
                {
                    if (father[v] == 0)
                    {       // not in-point
                        if (match[v])
                        {           // has matched
                            push(match[v]);       // match[v] becomes out-point
                            father[v] = u;       // v becomes in-point
                        }
                        else
                        {
                            father[v] = u;       // node v is another end
                            return v;
                        }
                    }
                }
            }
    }
    return 0;
}
void augment(int finish)
{
    int u = finish, v, w;
    while (u)
    {
        v = father[u];
        w = match[v];
        match[u] = v;
        match[v] = u;
        u = w;
    }
}
int graph_max_match()
{
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (match[i] == 0)
        {
            int finish = find_augment(i);
            if (finish)
            {
                augment(finish);
                ans += 2;
            }
        }
    return ans;
}
/*void standard_do()
{
    scanf("%d", &n);
    mapinit();
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) insert(a, b);
    printf("%d\n", graph_max_match());
    for (int i = 1; i <= n; ++i)
        if (match[i])
        {
            printf("%d %d\n", i, match[i]);
            match[match[i]] = 0;
        }
}*/
bool map[N][N];
int d[N], c[N];
int main()
{
    int T, x, y; scanf("%d", &T);
    for (int ca = 1; ca <= T; ++ca)
    {
        scanf("%d%d", &n, &m);
        mapinit();
        memset(map, 0, sizeof(map));
        memset(d, 0, sizeof(d));
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d%d", &x, &y);
            map[x][y]++, map[y][x]++;
            d[x]++, d[y]++;
        }
        for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
    }
    return 0;
}
