#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

tuple<int, int, int> Sol(const vector<pii>& v, int xm, int ym, int m) {
	const int n = v.size();
	int ret = 1, rx = v[0].first, ry = v[0].second;
	for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
		int mx = min(v[i].first - v[i].second, v[j].first - v[j].second);
		int my = min(v[i].first + v[i].second, v[j].first + v[j].second);
		for (auto& [cx, cy] : vector<pii>{ { mx, my }, { mx - 1, my }, { mx, my - 1 } }) {
			if (cx + cy & 1 || -cx + cy & 1) continue;
			int x = (cx + cy) / 2 + m / 2, y = (-cx + cy) / 2, cnt = 0;
			for (int k = 0; k < n; k++) {
				int d = abs(x - v[k].first) + abs(y - v[k].second);
				if (d <= m / 2) cnt++;
			}
			if (ret < cnt) ret = cnt, rx = x, ry = y;
		}
	}
	rx = min(max(rx, 0), xm);
	ry = min(max(ry, 0), ym);
	return { ret, rx, ry };
}

int main() {
	int xm, ym, n, m; cin >> xm >> ym >> n >> m;
	vector<pii> v(n);
	for (auto& [a, b] : v) cin >> a >> b;
	auto [res, x, y] = Sol(v, xm, ym, m);
	cout << x << ' ' << y << '\n' << res << '\n';
}