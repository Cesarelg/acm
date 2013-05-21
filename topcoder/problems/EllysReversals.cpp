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
#include <cstring>
#include <cmath>
using namespace std;
class EllysReversals {
public:
    string st(string s) {
        int n = s.length();
        vector<string> d;
        for (int i = 0; i+1 < n; i += 2) {
            string a = s.substr(i, 2);
            sort(a.begin(), a.end());
            d.push_back(a);
        }
        sort(d.begin(), d.end());
        string ans = "";
        for (int i = 0; i < d.size(); ++i)
            ans = ans + d[i];
        if (n&1) ans = ans + s[n-1];
        return ans;
    }
    int getMin(vector <string> words) {
        int k = words.size();
        for (int i = 0; i < k; ++i) words[i] = st(words[i]);
        sort(words.begin(), words.end());
        int now = 1, tot = 0;
        for (int i = 1; i < k; ++i)
            if (words[i] == words[i-1]) now = now + 1;
            else {
                tot += now / 2;
                now = 1;
            }
        tot += now / 2;//������Ϊû����仰...��ûAK
        return k - tot * 2;
    }
};
