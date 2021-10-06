#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, k, flag = 0; cin >> n >> k;
	vector<vector<int>> ans; vector<int> h;

	if (k > n) {
		ans.push_back({});
		for (int i = 1; i <= n; i++) ans.back().push_back(i);
		h.push_back(k);
		n--, k = 1, flag = 1;
	}

	vector<int> v(n);
	for (int i = 0; i < n; i++) v[i] = k + i;
	for (int sz = n + k - 1, box_sz = sz + 1 >> 1; sz >= 1; sz -= box_sz, box_sz = sz + 1 >> 1) {
		ans.push_back({}); h.push_back(box_sz);
		for (int i = 0; i < n; i++) if (v[i] >= box_sz) {
			v[i] -= box_sz;
			ans.back().push_back(i + 1 + flag);
		}
	}

	cout << h.size() << '\n';
	for (int i = 0; i < h.size(); i++) {
		cout << ans[i].size() << ' ' << h[i] << '\n';
		for (const auto& j : ans[i]) cout << j << ' ';
		cout << '\n';
	}
}