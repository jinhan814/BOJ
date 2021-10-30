#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int n, mx; pii v[50'000];
set<pii> S; map<pii, bitset<4>> visited;

pii Move(pii pos, int d) {
	const int nx = pos.first + "1012"[d] - '1';
	const int ny = pos.second + "2101"[d] - '1';
	return { nx, ny };
}

int DFS(int x, int y, int d) {
	int ret = 0;
	for (pii pos{ x, y }; !visited[pos][d];) {
		visited[pos][d] = 1; ret++;
		const pii a = Move(Move(pos, d), d + 3 & 3);
		const pii b = Move(pos, d + 3 & 3);
		if (S.count(a)) pos = a, d = d + 1 & 3;
		else if (S.count(b)) pos = b;
		else d = d + 3 & 3;
	}
	return ret;
}

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) { auto& [x, y] = v[i]; cin >> x >> y; }
	const int mn_x = min_element(v, v + n, [](const pii& a, const pii& b) { return a.first < b.first; })->first;
	const int mn_y = min_element(v, v + n, [](const pii& a, const pii& b) { return a.second < b.second; })->second;
	for (int i = 0; i < n; i++) { auto& [x, y] = v[i]; x -= mn_x, y -= mn_y; S.insert({ x, y }); }
	for (const auto& [x, y] : S) {
		for (int d = 0; d < 4; d++) {
			if (visited[{ x, y }][d]) continue;
			if (S.count(Move({ x, y }, d))) continue;
			mx = max(mx, DFS(x, y, d));
		}
	}
	cout << mx << '\n';
}