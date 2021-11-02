#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, mn = 1e9; cin >> n;
	vector<int> v; v.reserve(n);
	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		for (; t; t--) v.push_back(i);
	}
	for (int st = 0; st < n; st++) {
		int cur = 0;
		for (int i = 0; i < n; i++) {
			const int en = st + i >= n ? st + i - n : st + i;
			const int val = v[i] <= en ? en - v[i] : n - v[i] + en;
			cur += val * val;
		}
		mn = min(mn, cur);
	}
	cout << mn << '\n';
}