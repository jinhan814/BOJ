#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

vector<int> GetPI(const vector<int>& s) {
    const int n = s.size(); vector<int> f(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) f[i] = ++j;
    }
    return f;
}

bool KMP(const vector<int>& s, const vector<int>& t) {
    const int n = s.size(), m = t.size();
    vector<int> f = GetPI(t);
    for (int i = 0, j = 0; i < n; i++) {
        while (j && s[i] != t[j]) j = f[j - 1];
        if (s[i] == t[j] && ++j == m) return 1;
    }
    return 0;
}

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n), w(n);
	for (auto& i : v) cin >> i;
	for (auto& i : w) cin >> i;
	sort(v.begin(), v.end()), sort(w.begin(), w.end());

	vector<int> a, b;
	for (int i = 0; i < n; i++) a.push_back(i ? v[i] - v[i - 1] : 360'000 - (v.back() - v[0]));
	for (int i = 0; i < n; i++) b.push_back(i ? w[i] - w[i - 1] : 360'000 - (w.back() - w[0]));
	for (int i = 0; i < n; i++) a.push_back(a[i]);
    cout << (KMP(a, b) ? "possible" : "impossible") << '\n';
}