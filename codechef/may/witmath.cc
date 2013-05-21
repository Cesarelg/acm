#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <ctime>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cmath>
using namespace std;


long long gcd(long long a, long long b) //����a��b�����Լ��
 {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long mod_mult(long long a, long long b, long long n) //����(a*b) mod n
{
    long long s = 0;
    a = a % n;
    while (b) {
        if (b & 1) {
            s += a;
            if (s >= n)
                s -= n;
        }
        a = a << 1;
        if (a >= n)
            a -= n;
        b = b >> 1;
    }

    return s;
}

long long mod_exp(long long a, long long b, long long n) //����(a^b) mod n
{
    long long d = 1;
    a = a % n;
    while (b >= 1) {
        if (b & 1)
            d = mod_mult(d, a, n);
        a = mod_mult(a, a, n);
        b = b >> 1;
    }
    return d;
}

bool Wintess(long long a, long long n) //��aΪ����n����Miller���Բ�ʵ�ֶ���̽��
{
    long long m, x, y;
    int i, j = 0;
    m = n - 1;
    while (m % 2 == 0) //����(n-1)=m*(2^j)�е�j��m,j=0ʱm=n-1,���ϵĳ���2ֱ��nΪ����
    {
        m = m >> 1;
        j++;
    }
    x = mod_exp(a, m, n);
    for (i = 1; i <= j; i++) {
        y = mod_exp(x, 2, n);
        if ((y == 1) && (x != 1) && (x != n - 1)) //����̽��
            return true; //����trueʱ,n�Ǻ���

        x = y;
    }
    if (y != 1)
        return true;
    return false;
}

bool miller_rabin(int times, long long n) //��n����s�ε�Miller����
{
    long long a;
    int i;
    if (n == 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    srand(time(NULL));
    for (i = 1; i <= times; i++) {
        a = rand() % (n - 1) + 1;
        if (Wintess(a, n))
            return false;
    }
    return true;
}
int gcd(int x, int y) {
    return (x)?gcd(y%x, x) : y;
}

int eular(int x) {
    int cnt = 0;
    for (int i = 1; i <= x; ++i)
        if (gcd(x, i) == 1) ++cnt;
    return cnt;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long x;
        cin >> x;
        while (!miller_rabin(12, x)) --x;
        cout << x << endl;
    }
    return 0;
}
