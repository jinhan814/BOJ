#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

using pii = pair<int, int>;

int32_t main() {
	fastio;
	int n, m, i = 0, res = 0; cin >> n >> m;
	vector<pii> v(n); map<int, int> M;
	for (auto& [a, b] : v) cin >> a >> b;
	sort(v.begin(), v.end());
	for (int a, b; m-- && cin >> a >> b; M[a] += b);
	priority_queue<int, vector<int>, greater<>> PQ;
	for (const auto& [a, b] : M) {
		while (i < n && v[i].first <= a) PQ.push(v[i++].second);
		while (PQ.size() && PQ.top() < a) PQ.pop();
		for (int i = 0; i < b && PQ.size(); i++) res++, PQ.pop();
	}
	cout << res << '\n';
}