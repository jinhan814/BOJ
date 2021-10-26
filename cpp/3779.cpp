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
    for (int c = 1, n; cin >> n && n; c++) {
        string s; cin >> s; auto f = GetPI(s);
        cout << "Test case #" << c << '\n';
        for (int i = 0; i < n; i++) {
            if (!f[i]) continue;
            const int sz = i + 1 - f[i];
            if ((i + 1) % sz == 0) cout << i + 1 << ' ' << (i + 1) / sz << '\n';
        }
        cout << '\n';
    }
}