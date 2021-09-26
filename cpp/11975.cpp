#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define sz(v) (int)((v).size())
#define all(v) (v).begin(), (v).end()
#define compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())

using point = pair<int, int>;
using line = pair<point, point>;

int main() {
	fastio;
	int n; string s; cin >> n >> s;
	vector<point> V{ point(0, 0) }; vector<line> E;
	for (int i = 0, x = 0, y = 0; i < n; i++) {
		const int d = string("ENWS").find(s[i]);
		int nx = x + "1012"[d] - '1';
		int ny = y + "2101"[d] - '1';
		V.push_back({ nx, ny });
		E.push_back({ point(x, y), point(nx, ny) });
		x = nx, y = ny;
	}
	for (auto& [a, b] : E) if (a > b) swap(a, b);
	compress(V); compress(E);
	cout << (2 - sz(V) + sz(E)) - 1 << '\n';
}