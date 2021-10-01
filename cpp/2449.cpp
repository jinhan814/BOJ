#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, cache[200][200];
vector<int> v;

int DFS(int l, int r) {
	if (r <= l) return 0;
	int& ret = cache[l][r];
	if (ret != -1) return ret; ret = 1e9;
	for (int i = l; i < r; i++) ret = min(ret, DFS(l, i) + DFS(i + 1, r) + (v[l] != v[r]));
	return ret;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int t; cin >> t; --t;
		if (v.empty() || v.back() != t) v.push_back(t);
	}
	memset(cache, -1, sizeof cache);
	cout << DFS(0, v.size() - 1) << '\n';
}