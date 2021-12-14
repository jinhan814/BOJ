#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
	fastio;
	int a, b; cin >> a >> b;
	if (a == b) return !(cout << 0 << '\n');
	queue<pair<int, string>> Q; Q.push({ a, "" });
	set<int> S; S.insert(a);
	while (Q.size()) {
		auto [cur, s] = Q.front(); Q.pop();
		if (cur == b) return !(cout << s << '\n');
		for (int i = 0; i < 4; i++) {
			if (!i && cur > 1e9 || i == 3 && !cur) continue;
			auto ns = s + "*+-/"[i];
			auto nxt = !i ? cur * cur : i == 1 ? cur << 1 : i == 3;
			if (S.count(nxt)) continue;
			Q.push({ nxt, ns }), S.insert(nxt);
		}
	}
	cout << -1 << '\n';
}