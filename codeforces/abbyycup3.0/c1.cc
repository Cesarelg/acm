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
using namespace std;
template <typename T> void checkMin(T &a, const T &b) { if (b < a) a = b; }
template <typename T> void checkMax(T &a, const T &b) { if (b > a) a = b; }

const int MAXN = 10000 + 9;
const int MAXM = 1000000 + 9;

const int INF = 1000000000;

struct edge{
    int x, y, f, c, next;
}e[MAXM];
int eid, p[MAXN];
int n, m, source, sink;
int d[MAXN], pre[MAXN], path[MAXN];
queue<int> q;
bool use[MAXN];
void insert(int x, int y, int f, int c) {
    e[eid].x = x;
    e[eid].y = y;
    e[eid].f = f;
    e[eid].c = c;
    e[eid].next = p[x];
    p[x] = eid++;
}
void insert1(int x, int y, int f, int c) {
    cout << x << " " << y << " " << f << " " << c << endl;
    insert(x, y, f, c);
    insert(y, x, 0, -c);
}
void insert2(int x, int y, int f, int c) {
    insert1(x, y, f, c);
    insert1(y, x, f, c);
}
void init(int _n, int _s, int _t) {
    memset(p, -1, sizeof(p));
    eid = 0;
    n = _n;
    source = _s;
    sink = _t;
}
bool spfa(int s) {
    memset(use, false, sizeof(use));
    int u, v;
    for (int i = 0; i < n; ++i) d[i] = INF;
    while (!q.empty()) q.pop();
    q.push(s);
    d[s] = 0;
    pre[s] = -1;
    use[s] = true;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (int i = p[u]; i != -1; i = e[i].next) {
            v = e[i].y;
            if ((e[i].f != 0) && (d[u] + e[i].c < d[v])) {
                d[v] = d[u] + e[i].c;
                pre[v] = u;
                path[v] = i;
                if (!use[v]) {
                    use[v] = true;
                    q.push(v);
                }
            }
        }
        use[u] = false;
    }
    return (d[sink] != INF);
}
int argument() {
    int delta = INF, res = 0;
    for (int i = sink; pre[i] != -1; i = pre[i])
        delta = min(delta, e[path[i]].f);
    for (int i = sink; pre[i] != -1; i = pre[i]) {
        e[path[i]].f -= delta;
        e[path[i] ^ 1].f += delta;
        res += e[path[i]].c * delta;
    }
    return res;
}
int mincostflow() {
    int sum = 0;
    while (spfa(source)) sum += argument();
    return sum;
}


int dy[] = {0, -1, 0, 1};
int dx[] = {-1, 0, 1, 0};

struct Task {
	int r, c;
	int mat[85][85];
	bool read() {
		if ( !(cin >> r >> c) ) return false;
		for ( int i = 0; i < r; ++i ) {
			for ( int j = 0; j < c; ++j ) {
				cin >> mat[r][c];
			}
		}
		return true;
	}
        void solve() {
		int rc = r * c, rc2 = 2 * rc, half = rc/2;
		int source = rc * 3 + 0;
		int sink = rc * 3 + 1;
		init(sink + 1, source, sink);
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				int h = i * c + j;
				if (h % 2 == 0) {
					for (int k = 0; k < half; ++k) {
						insert1(k, h + rc, 1, k+1 != mat[i][j]);
					} 
				} else {
					for (int k = 0; k < half; ++k) {
						insert1(h + rc, k + half, 1, k+1 != mat[i][j]);
					}
				}
			}
		}
		for (int i = 0; i < rc; ++i) {
			if (i < half) {
				insert1(source, i, 1, 0);
			} else {
				insert1(i, sink, 1, 0);
			}
		}
		for (int i = 0; i < rc; ++i) {
			if (i % 2 == 0) {
				insert1(i + rc, i + rc2, 1, 0);
			} else {
				insert1(i + rc2, i + rc, 1, 0);
			}
		}
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				for (int k = 0; k < 4; ++k) {
					int ii = i + dx[k], jj = j + dy[k];
					if ( 0 <= ii && ii < r && 0 <= jj && jj < c ) {
						insert1(i * c + j + rc2, ii * c + jj + rc2, 1, 0);
					}
				}		
			}
		}
		int ans = mincostflow();
		cout << ans << endl;
	}
} task;

int main() {
	while ( task.read() ) task.solve();
}
