#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

constexpr int INF = int(1e18) + 7;
using pii = pair<int, int>;

int32_t main() {
	fastio;
	int x1, y1, d1; cin >> x1 >> y1 >> d1;
	int x2, y2, d2; cin >> x2 >> y2 >> d2;

	auto Sol = [&]() -> pii {
		const bool parity_1 = d1 & 1 ? ~(x1 + y1) & 1 : (x1 + y1) & 1;
		const bool parity_2 = d2 & 1 ? ~(x2 + y2) & 1 : (x2 + y2) & 1;
		if (parity_1 != parity_2) return { INF, INF };
		for (int k = 0; k < 4; k++) {
			int nx = x1 + ("1012"[k] - '1') * d1;
			int ny = y1 + ("2101"[k] - '1') * d1;
			if (abs(nx - x2) + abs(ny - y2) <= d2) return { nx, ny };
		}
		for (int k = 0; k < 4; k++) {
			int nx = x2 + ("1012"[k] - '1') * d2;
			int ny = y2 + ("2101"[k] - '1') * d2;
			if (abs(nx - x1) + abs(ny - y1) <= d1) return { nx, ny };
		}
		return { INF, INF };
	};

	auto [x, y] = Sol();
	if (x == INF) cout << "impossible" << '\n';
	else cout << x << ' ' << y << '\n';
}