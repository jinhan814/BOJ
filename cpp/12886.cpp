#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MX = 1'000;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

int main() {
	fastio;
	int a, b, c; cin >> a >> b >> c;
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (b > c) swap(b, c);

	cout << [&]() -> bool {
		set<pii> visited[MX + 1];
		queue<tii> Q;
		Q.push({ a, b, c }), visited[a].insert({ b, c });
		while (Q.size()) {
			auto [x, y, z] = Q.front(); Q.pop();
			if (x == y && y == z) return 1;
			for (auto [t1, t2, t3] : vector<tii>{
				{ x + x, y - x, z },
				{ x + x, y, z - x },
				{ x, y + y, z - y }
			}) {
				if (!t1 || !t2 || !t3) continue;
				if (t1 > t2) swap(t1, t2);
				if (t1 > t3) swap(t1, t3);
				if (t2 > t3) swap(t2, t3);
				if (visited[t1].count({ t2, t3 })) continue;
				Q.push({ t1, t2, t3 }), visited[t1].insert({ t2, t3 });
			}
		}
		return 0;
	}() << '\n';
}