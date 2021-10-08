#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t
using pii = pair<int, int>;

int32_t main() {
	fastio;
	int n; cin >> n;
	vector<pii> v(n);
	for (auto& [a, b] : v) cin >> a >> b, b += a;
	sort(v.begin(), v.end());

	auto cmp = [](const pii& a, const pii& b) -> bool {
		return a.second > b.second;
	};

	auto Check = [&](int mid) -> bool {
		priority_queue<pii, vector<pii>, decltype(cmp)> PQ(cmp);
		for (int cur = v[0].first, cnt = 0, i = 0; cnt < n; cnt++) {
			while (i < n && v[i].first <= cur) PQ.push(v[i++]);
			if (PQ.size() && PQ.top().second < cur) return 0;
			if (PQ.empty()) cur = v[i++].first + mid;
			else PQ.pop(), cur += mid;
		}
		return 1;
	};

	int lo = 0, hi = 1e10 + 7;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (Check(mid)) lo = mid;
		else hi = mid;
	}
	cout << lo << '\n';
}