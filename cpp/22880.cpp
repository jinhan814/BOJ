#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
	fastio;
	int n, ans = 1; cin >> n;
	vector<int> v, cnt;
	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		if (v.empty() || v.back() < t) v.push_back(t), cnt.push_back(1);
		else cnt.back()++;
	}
	for (int i = 0; i + 1 < cnt.size(); i++) ans = 1LL * ans * (cnt[i] + 1) % MOD;
	cout << ans << '\n';
}