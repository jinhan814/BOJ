#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
using tii = tuple<int, int, int>;

int main() {
	fastio;
	int n, k; cin >> n >> k;
	vector<int> inv(n), cnt(n);
	vector<vector<int>> v(n);
	for (int i = 0; i < n; i++) cin >> inv[i];
	for (int i = 0, t; i < n; i++) cin >> t, v[inv[i] - 1].push_back(t);
	for (int i = 0; i < n; i++) sort(v[i].begin(), v[i].end());

	auto GetLim = [&]() -> int {
		int lo = 0, hi = n;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1, t = 0;
			for (int i = 0; i < n; i++) t += min<int>(mid, v[i].size());
			if (t < k) lo = mid;
			else hi = mid;
		}
		return hi;
	};
	auto lim = GetLim();
	for (int i = 1; i < lim; i++) cout << -1 << ' ';

	int64_t res = 0;
	priority_queue<pii, vector<pii>, greater<>> cand;
	priority_queue<pii> used;
	priority_queue<tii, vector<tii>, greater<>> que;
	for (int i = 0; i < n; i++) for (const auto& j : v[i]) cand.push({ j, i });
	for (int i = 0; i < k; i++) {
		while (cnt[cand.top().second] >= lim) cand.pop();
		res += cand.top().first, cnt[cand.top().second]++;
		used.push(cand.top()), cand.pop();
	}
	while (cand.size()) cand.pop();
	for (int i = 0; i < n; i++) {
		for (int j = cnt[i]; j < min<int>(lim, v[i].size()); j++) cand.push({ v[i][j], i });
		for (int j = lim; j < v[i].size(); j++) que.push({ j + 1, v[i][j], i });
	}

	cout << res << ' ';
	for (int i = lim + 1; i <= n; i++) {
		while (que.size() && get<0>(que.top()) <= i) {
			auto [a, b, c] = que.top(); que.pop();
			cand.push({ b, c });
		}
		while (cand.size() && cand.top().first < used.top().first) {
			auto t1 = cand.top(); cand.pop();
			auto t2 = used.top(); used.pop();
			res += t1.first - t2.first;
			cnt[t1.second]++, cnt[t2.second]--;
			used.push(t1), cand.push(t2);
		}
		cout << res << ' ';
	}
	cout << '\n';
}