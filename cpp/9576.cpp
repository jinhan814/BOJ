#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, m, cnt = 0; cin >> n >> m;
		vector<pii> v(m);
		for (auto& [a, b] : v) cin >> a >> b;
		sort(v.begin(), v.end());
		priority_queue<int, vector<int>, greater<>> PQ;
		for (int t = 1, i = 0; t <= n; t++) {
			while (i < m && v[i].first <= t) PQ.push(v[i++].second);
			while (PQ.size() && PQ.top() < t) PQ.pop();
			if (PQ.size()) cnt++, PQ.pop();
		}
		cout << cnt << '\n';
	}
}