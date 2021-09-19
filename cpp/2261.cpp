#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

struct p {
	int x, y;
	bool operator < (const p& i) const {
		if (y != i.y) return y < i.y;
		return x < i.x;
	}
	friend int dist(const p& a, const p& b) {
		return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	}
};

int main() {
	fastio;
	//input
	int n; cin >> n;
	vector<p> v(n);
	for (auto& [a, b] : v) cin >> a >> b;

	//sort
	sort(v.begin(), v.end(), [&](const p& a, const p& b) {
		return a.x < b.x;
	});

	//sweeping
	set<p> S{ v[0], v[1] };
	int mn = dist(v[0], v[1]);
	for (int i = 2, j = 0; i < n; i++) {
		while (j < i) {
			int d = v[i].x - v[j].x;
			if (d * d > mn) S.erase(v[j++]);
			else break;
		}
		int d = sqrt(mn) + 1;
		auto lo = S.lower_bound({ -INF, v[i].y - d });
		auto hi = S.upper_bound({ INF, v[i].y + d });
		for (auto it = lo; it != hi; it++) {
			if (mn > dist(v[i], *it)) mn = dist(v[i], *it);
		}
		S.insert(v[i]);
	}
	cout << mn << '\n';
}