#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, v[1000], cnt[1000];

void Move() {
	vector<int> t;
	for (int i = 0; i < n; i += 3) t.push_back(v[1 + i]);
	for (int i = 0; i < n; i += 3) t.push_back(v[2 + i]);
	for (int i = 0; i < n; i += 3) t.push_back(v[3 + i]);
	for (int i = 0; i < n; i++) v[i + 1] = t[i];
}

int main() {
	fastio;
	cin >> n >> m; iota(v + 1, v + n + 1, 1);
	for (int i = 0; i < m; i++, Move()) {
		string s; cin >> s;
		int t = s == "first" ? 1 : s == "second" ? 2 : 3;
		for (int i = 0; i < n; i += 3) cnt[v[t + i]]++;
	}
	for (int i = 1; i <= n; i++) if (cnt[i] == m) cout << i << ' ';
	cout << '\n';
}