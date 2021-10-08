#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Info { int s, e, val; };

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<int> v(n);
	vector<Info> I(m);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (auto& [s, e, val] : I) cin >> s >> e >> val, val = v[val - 1] * (e - s);
	sort(I.begin(), I.end(), [](const Info& a, const Info& b) { return a.s ^ b.s ? a.s < b.s : a.e < b.e; });

	vector<int64_t> DP(m);
	for (int i = m - 1; i >= 0; i--) {
		DP[i] = I[i].val;
		if (i != m - 1) DP[i] = max(DP[i], DP[i + 1]);
		auto it = lower_bound(I.begin(), I.end(), Info{ I[i].e, -1, -1 }, [](const Info& a, const Info& b) { return a.s < b.s; });
		if (it != I.end()) DP[i] = max(DP[i], I[i].val + DP[it - I.begin()]);
	}
	cout << DP[0] << '\n';
}