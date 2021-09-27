#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Info {
	int x, y, val;
	bool operator< (const Info& i) const { return x < i.x; }
};

int main() {
	fastio;
	int n, ans = 0; cin >> n;
	vector<Info> v(n);
	for (auto& [x, y, val] : v) cin >> x >> y >> val;

	auto Sol = [&]() -> int {
		vector<int> DP(n);
		for (int i = 0; i < n; i++) {
			DP[i] = v[i].val;
			for (int j = 0; j < i; j++) if (v[j].y < v[i].y) DP[i] = max(DP[i], DP[j] + v[i].val);
		}
		return *max_element(DP.begin(), DP.end());
	};

	sort(v.begin(), v.end()); ans = max(ans, Sol());
	sort(v.rbegin(), v.rend()); ans = max(ans, Sol());
	cout << ans << '\n';
}