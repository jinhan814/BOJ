#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int B = 25000;
constexpr int SZ = 1000000 / B;

using i64 = long long;
using pii = pair<int, int>;

#define F(X, Y) ((x - X) * (x - X) <= (r + y - Y) * (r - y + Y))

vector<pii> Bucket[SZ + 1][SZ + 1];

int Sol(i64 x, i64 y, i64 r) {
	int ret = 0;
	for (int i = 0; i <= SZ; i++) for (int j = 0; j <= SZ; j++) {
		const int xm = i * B, xM = xm + B - 1;
		const int ym = j * B, yM = ym + B - 1;
		const int res = F(xm, ym) + F(xm, yM) + F(xM, ym) + F(xM, yM);
		const int f1 = xm <= x && x <= xM;
		const int f2 = ym <= y && y <= yM;
		if (res == 4) ret += Bucket[i][j].size();
		else if (res || f1 && f2 ||
			f1 && abs(min(y - ym, yM - y)) <= r ||
			f2 && abs(min(x - xm, xM - x)))
			for (const auto& [px, py] : Bucket[i][j]) if (F(px, py)) ret++;
	}
	return ret;
}

int main() {
	fastio;
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		Bucket[x / B][y / B].push_back({ x, y });
	}
	int q; cin >> q;
	while (q--) {
		int x, y, r; cin >> x >> y >> r;
		cout << Sol(x, y, r) << '\n';
	}
}