#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
	fastio;
	int n, m, ans = 0; cin >> n >> m;
	priority_queue<int, vector<int>, greater<>> PQ;
	for (int t; n-- && cin >> t; PQ.push(t));
	while (m--) {
		int t1 = PQ.top(); PQ.pop();
		int t2 = PQ.top(); PQ.pop();
		PQ.push(t1 + t2), PQ.push(t1 + t2);
	}
	while (PQ.size()) ans += PQ.top(), PQ.pop();
	cout << ans << '\n';
}