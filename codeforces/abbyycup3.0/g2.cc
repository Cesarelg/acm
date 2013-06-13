// =====================================================================================
// 
//       Filename:  g1.cc
// 
//    Description:  implement
// 
//        Version:  1.0
//        Created:  2013年06月12日 21时40分32秒
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
using namespace std;
template <typename T> void checkMin(T &a, const T &b) { if (b < a) a = b; }
template <typename T> void checkMax(T &a, const T &b) { if (b > a) a = b; }


const int N = 2000 + 10;

int ch[N*N/2][26], d[N*N/2], tot;

int insert(char *str, int st, int ed) {
    int j = 0, ret = 0;
    for (int i = 0; str[i]; ++i) {
        int x = str[i] - 'a';
        if (ch[j][x]) j = ch[j][x];
        else {
            ch[j][x] = ++tot;
            j = ch[j][x];
            memset(ch[j], 0, sizeof(ch[j]));
            d[j] = 0;
        }
        if (i >= st && i <= ed) {
            if (!d[j]) {
                d[j] = 1;
                ++ret;
            }
        }
    }
    return ret;
}

void getnext(char *str, int next[]) {
    next[0] = -1;
    for (int i = 1, j = -1; str[i]; ++i) {
        while (~j && str[i] != str[j+1]) j = next[j];
        if (str[i] == str[j+1]) ++j;
        next[i] = j;
    }
}

char dat[20][N];
int n, next[N], l[20], r[20];
int last;

int count(char *str, int len, char *dest) {
    int ret = 0;
    for (int i = 0, j = -1; dest[i]; ++i) {
        while (~j && str[j+1] != dest[i]) j = next[j];
        if (str[j+1] == dest[i]) ++j;
        if (j == len - 1) {
            j = next[j];
            ++ret;
        }
    }
    return ret;
}
int count(char *str, int len, int x) {
    return count(str, len, dat[x]);
}

int gao(char *str) {
    getnext(str, next);
    int len = strlen(str);
    int ll = -1, rr = len + 1;
    for (int i = 1; i <= 10; ++i) {
        int left = 1, right = len, mid;
        while (left < right) {
            if (left + 1 == right) {
                if (count(str, left, i) > r[i]) left = right;
                break;
            }
            mid = (left + right) >> 1;
            if (count(str, mid, i) > r[i]) left = mid + 1;
            else right = mid;
        }
        if (count(str, left, i) > r[i]) return 0;
        checkMax(ll, left);
        left = 1, right = len;
        while (left < right) {
            if (left + 1 == right) {
                if (count(str, right, i) >= l[i]) left = right;
                break;
            }
            mid = (left + right + 1) >> 1;
            if (count(str, mid, i) >= l[i]) left = mid;
            else right = mid - 1;
        }
        if (count(str, left, i) < l[i]) return 0;
        checkMin(rr, left);
    }
    if (rr < ll) return 0;
    return insert(str, ll - 1, rr - 1);
}
char str[N];

int main (int argc, char *argv[]) {
    while (scanf("%s", str) == 1) {
        tot = 0;
        memset(ch[0], 0, sizeof(ch[0]));
        d[0] = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%s%d%d", dat[i], &l[i], &r[i]);
        int len = strlen(str), ret = 0;

        last = 0;
        for (int i = 0; i < len; ++i) {
            ret += gao(str+i);
        }
        printf("%d\n", ret);
    }
    return 0;
}
