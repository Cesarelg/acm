// =====================================================================================
// 
//       Filename:  a.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  2013年06月01日 22时00分09秒
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Boyang Yang (barty), maiL@barty.ws
//        Company:  http://barty.ws
// 
// =====================================================================================


#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cstring>
#define MAXN 2024
#define MAXM 10485760
using namespace std;
typedef long long LL;
const LL INF = 100000000000000000LL;
const LL mod = 1000002013LL;
namespace flow {
	struct edge{
	    int x, y, next;
        LL f, c;
	}e[MAXM];
	int eid, p[MAXN];
	int n, m, source, sink;
	LL d[MAXN];
	int pre[MAXN], path[MAXN];
	queue<int> q;
	bool use[MAXN];
	void insert(int x, int y, LL f, LL c)
	{
	    e[eid].x = x;
	    e[eid].y = y;
	    e[eid].f = f;
	    e[eid].c = c;
	    e[eid].next = p[x];
	    p[x] = eid++;
	}
	void insert1(int x, int y, LL f, LL c)
	{
	    insert(x, y, f, c);
	    insert(y, x, 0, -c);
	}
	void insert2(int x, int y, LL f, LL c)
	{
	    insert1(x, y, f, c);
	    insert1(y, x, f, c);
	}
	void mapinit()
	{
	    memset(p, -1, sizeof(p));
	    eid = 0;
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
	LL argument()
	{
	    LL delta = INF, res = 0;
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
	LL maxcostflow()
	{
	    LL sum = 0;
	    while (spfa(source)) sum += argument();
	    return sum;
	}
}

/*int tsize, table[MAXN*2];
void init_table() {
    sort(table, table+tsize);
    tsize = unique(table, table+tsize)-table;
}

int get_index(int key) {
    return lower_bound(table, table+tsize, key)-table;
}*/

int n, m, st[MAXN], ed[MAXN], p[MAXN];
int in[MAXN], out[MAXN];

LL calc(int x) {
    LL xx = x, nn = n;
    xx = abs(xx);
    if (xx == 0) return 0;
    return (nn + nn - xx + 1LL) * xx / 2LL;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int ca = 1; ca <= T; ++ca) {
        scanf("%d%d", &n, &m);
        //tsize = 0;
        LL tots = 0;
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &st[i], &ed[i], &p[i]);
            tots += calc(st[i]-ed[i]) * p[i];
        }
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        for (int i = 1; i <= m; ++i) {
            in[st[i]] += p[i];
            out[ed[i]] += p[i];
        }
        flow::mapinit();
        flow::source = n*2 + 1;
        flow::sink = n*2 + 2;
        flow::n = n*2 + 2;
/*        for (int i = 0; i < tsize; ++i)
            for (int j = 0; j < tsize; ++j)
                flow::insert1(i + 1, tsize + j + 1, INF, calc(table[i]-table[j]));
        for (int i = 0; i < tsize; ++i) {
            if (in[i] > 0) flow::insert1(flow::source, i + 1, in[i], 0LL);
            if (out[i] > 0) flow::insert1(tsize + i + 1, flow::sink, out[i], 0LL);
        }*/
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                flow::insert1(i, j+n, INF, calc(i-j));
        for (int i = 1; i <= n; ++i) {
            if (in[i] > 0) flow::insert1(flow::source, i, in[i], 0LL);
            if (out[i] > 0) flow::insert1(i+n, flow::sink, out[i], 0LL);
        }
//        cout << tots << " " << flow::maxcostflow() << endl;
        printf("Case #%d: %lld\n", ca, tots - flow::maxcostflow());
    }

    return 0;
}
