#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

vector<int> GetPI(const string& s) {
    int n = s.size(); vector<int> f(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) f[i] = ++j;
    }
    return f;
}

int main() {
	fastio;
    int n; string s; cin >> n >> s;

    auto Sol = [&]() -> int {
        auto f = GetPI(s);
        for (int i = 0; i < n; i++) {
            int sz = i + 1, flag = 1;
            if (f.back() < n % sz) continue;
            for (int j = i + sz; j < n; j += sz)
                if (f[j] < sz) { flag = 0; break; }
            if (flag) return sz;
        }
        return n;
    };

    cout << Sol() << '\n';
}