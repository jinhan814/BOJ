#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

vector<int> GetPI(const vector<int>& s) {
    int n = s.size(); vector<int> f(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) f[i] = ++j;
    }
    return f;
}

int main() {
	fastio;
    int n; cin >> n;
    vector<int> v(n);
    for (int i = n - 1; i >= 0; i--) cin >> v[i];

    auto f = GetPI(v);
    int mx = *max_element(f.begin(), f.end());
    int cnt = count(f.begin(), f.end(), mx);
    if (mx) cout << mx << ' ' << cnt << '\n';
    else cout << -1 << '\n';
}