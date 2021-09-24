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
    string a, b, ans; cin >> a >> b;
    vector<int> f = GetPI(b), DP(a.size());
    for (int i = 0, j = 0; i < a.size(); i++) {
        ans.push_back(a[i]);
        while (j && a[i] != b[j]) j = f[j - 1];
        if (a[i] == b[j] && ++j == b.size()) {
            ans.erase(ans.end() - b.size(), ans.end());
            j = DP[ans.size()];
        }
        DP[ans.size()] = j;
    }
    cout << ans << '\n';
}