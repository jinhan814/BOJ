#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Info { int s, e, val; };

int main() {
	fastio;
	int n; cin >> n;
	vector<Info> I(n);
	for (auto& [s, e, val] : I) cin >> s >> e >> val;
	sort(I.begin(), I.end(), [](const Info& a, const Info& b) { return a.s ^ b.s ? a.s < b.s : a.e < b.e; });

	vector<int> DP(n);
	for (int i = n - 1; i >= 0; i--) {
		DP[i] = I[i].val;
		if (i != n - 1) DP[i] = max(DP[i], DP[i + 1]);
		auto it = upper_bound(I.begin(), I.end(), Info{ I[i].e, -1, -1 }, [](const Info& a, const Info& b) { return a.s < b.s; });
		if (it != I.end()) DP[i] = max(DP[i], I[i].val + DP[it - I.begin()]);
	}
	cout << DP[0] << '\n';
}