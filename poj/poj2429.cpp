#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#define MAXN 128
#define L UL
#define UL unsigned __int64
using namespace std;
int list[9] = {2, 3, 5, 7, 11, 13, 17, 19, 61};
//6λʹ��2,3,5���ɣ�10λ����7��61������__int64��Χ


UL mod_pro(UL x, UL y, UL n)
{
    UL ret = 0, tmp = x % n;
    while(y)
    {
        if((y & 1) && ((ret += tmp)>n)) ret -= n;
        if((tmp <<= 1) > n) tmp -= n;
        y >>= 1;
    }
    return ret;
}
UL mod(UL a, UL b, UL c)
{
    UL ret = 1;
    while(b)
    {
        if(b & 1) ret = mod_pro(ret, a, c);
        a = mod_pro(a, a, c);
        b >>= 1;
    }
    return ret;
}

bool is_prime(UL n)
{
    if(n == 2 || n == 3 || n == 7 || n == 11)
        return true;
    if(n & 1 == 0)
        return false;
    UL k = 0, m, a, i;
    int t = 0;
    for(m = n-1; !(m & 1); m >>= 1, k++);
    while(t < 9)
    {
        a = mod(list[t] % (n - 2) + 2, m, n);
        if(a != 1)
        {
            for(i = 0;(i < k) && (a != n - 1); i++)
                a = mod_pro(a, a, n);
            if(i >= k)return false;
        }
        t++;
    }
    return true;
}
UL GCD(UL x, UL y)
{
    return y ? GCD(y, x % y) : x;
}
UL pollard_rho(UL n, int c)
{
    UL x, y, d, i = 1, k = 2;
    x = rand() % (n - 1) + 1;
    y = x;
    while(true)
    {
        ++i;
        x = (mod_pro(x, x, n) + c) % n;
        d = GCD(y - x, n);
        if (1 < d && d < n) return d;
        if (x == y) return n;
        if (i == k) y = x, k <<= 1;
    }
}
UL res;
UL rx, ry, temp;
int facl = 0, nl = 0;
UL num[MAXN], factor[MAXN];
UL g, l;//gcd, lcm
void findFactor(UL n, int k)
{
    //factor[++facl] = n;����
    if (n == 1) return;
    if (is_prime(n))
    {
        factor[++facl] = n;//������
        return ;
    }
    UL p = n;
    while(p >= n)
        p = pollard_rho(p, k--);
    findFactor(p, k);
    findFactor(n / p, k);
}

void dfs(UL deep, UL x, UL y)
{
    if (deep == nl + 1)
    {
        if (x + y <= res)
        {
            res = x + y;
            rx = x;
            ry = y;
        }
        return;
    }
    dfs(deep + 1, x * num[deep], y);
    dfs(deep + 1, x, y * num[deep]);
}
void make_num()
{
    memset(num, 0, sizeof(num));
    nl = 0;
    for (int i = 1; i <= facl; ++i)
    {
        if (temp % factor[i] == 0)
        {
            num[++nl] = 1;
            while (temp % factor[i] == 0)
            {
                temp /= factor[i];
                num[nl] *= factor[i];
            }
        }
    }
    if (nl == 0) num[++nl] = 1;
}

int main()
{

    while (cin >> g >> l)
    {
        temp = l / g;
        res = l * 2;
        facl = 0;
        findFactor(temp, 107);
        make_num();
        dfs(1, 1, 1);
        if (rx > ry) swap(rx, ry);
        cout << rx * g << " " << ry * g << endl;
    }
    return 0;
}
