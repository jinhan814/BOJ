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

int KMP(const string& s, const string& t) {
    int n = s.size(), m = t.size(), ret = 0;
    vector<int> f = GetPI(t);
    for (int i = 0, j = 0; i < n; i++) {
        while (j && s[i] != t[j]) j = f[j - 1];
        if (s[i] == t[j] && ++j == m) ret++, j = f[j - 1];
    }
    return ret;
}

int main() {
	fastio;
    string A, B; cin >> A >> B; B += B; B.pop_back();
    cout << KMP(B, A) << '\n';
}