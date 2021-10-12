#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m, q, ans = 0; cin >> n >> m >> q;
	vector<pair<int, int>> v(q + 1);
	for (auto& [a, b] : v) cin >> a >> b;

	auto GetDist = [&n, &m](int t1, int pos1, int t2, int pos2) -> int {
		if (t1 == t2) return abs(pos1 - pos2);
		if (t1 > t2) swap(t1, t2), swap(pos1, pos2);
		if (t1 == 1 && t2 == 2) return min(m + pos1 + pos2, 2 * n - pos1 - pos2 + m);
		if (t1 == 1 && t2 == 3) return pos1 + pos2;
		if (t1 == 1 && t2 == 4) return n - pos1 + pos2;
		if (t1 == 2 && t2 == 3) return pos1 + m - pos2;
		if (t1 == 2 && t2 == 4) return n + m - pos1 - pos2;
		if (t1 == 3 && t2 == 4) return min(n + pos1 + pos2, 2 * m - pos1 - pos2 + n);
	};

	for (const auto& [t1, pos1] : v) {
		const auto& [t2, pos2] = v.back();
		ans += GetDist(t1, pos1, t2, pos2);
	}
	cout << ans << '\n';
}