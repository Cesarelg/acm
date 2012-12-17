#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define PI acos(-1)
#define eps 1e-6

using namespace std;
const int MAXN = 50009;

struct Point { // ��ṹ��
    int x, y;
};

Point p[MAXN], cHull[MAXN], pivot;
double L;
int N;

//AB * AC
int cross(const Point &A, const Point &B, const Point &C) { // ��Ĳ��
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

int distsqr(const Point &A, const Point &B) { // ��������֮������ƽ��
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

double dist(const Point &A, const Point &B)
{
    return sqrt((double)distsqr(A, B));
}

bool cmp(const Point &a, const Point &b) { // ���ݼ��Ǵ�С��������ıȽϺ���
    int t = cross(pivot, a, b); // pivot�ǵ㼯��y������С�ĵ�
    return t > 0 || (t == 0 && distsqr(pivot, a) < distsqr(pivot, b));
}

void convexHull(Point p[], int n, Point stck[], int &m) {
    int i, k, top;
    if (n < 3) { // �������С��3��ֱ�ӱ��浱ǰ�ĵ㼯
        for (i = 0; i < n; ++i) stck[i] = p[i];
        m = n;
        return;
    }
    for (k = 0, i = 1; i < n; ++i) // �ҳ�y������С�ĵ�
        if (p[i].y < p[k].y || (p[i].y == p[k].y && p[i].x < p[k].x))
            k = i;
    pivot = p[k]; // ��pivot�ŵ�p[0]��λ��
    p[k] = p[0];
    p[0] = pivot;
    sort(p + 1, p + n, cmp); // ���ݼ��Ǵ�С��������
    stck[0] = p[0];  // ��ʼʱ�������ĵ㼯�е�һ�͵ڶ���Ԫ�ؽ�ջ
    stck[1] = p[1];
    top = 1;
    for (i = 2; i < n; ++i) {
        while (top > 0 && cross(p[i], stck[top], stck[top - 1]) >= 0) // ɾ������ĵ�
            --top;
        stck[++top] = p[i]; // ��ǰ���ʵĵ��ջ
    }
    m = top + 1; // ͹���ĵ���
}

bool input() {
    int i;
    if (scanf("%d%lf", &N, &L) == EOF) return false;
    for (i = 0; i < N; ++i) // ����������
        scanf("%d%d", &p[i].x, &p[i].y);
    return true;
}

void solve() {
    int i, j, d, ans = 0, M;
    convexHull(p, N, cHull, M); // ����͹��
    double s = 0;
    for (i = 0; i < M; ++i)
        s += dist(cHull[i], cHull[(i + 1) % M]);
    s += 2 * PI * L;
    printf("%d\n", (int)(round(s) + eps));
}

int main() {
    while (input()) solve();
    return 0;
}
