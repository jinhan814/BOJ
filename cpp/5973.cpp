#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int main() {
	fastio;
	int n, cnt = 0; cin >> n;
	vector<pii> v(n); map<pii, int> M;
	for (auto& [a, b] : v) cin >> a >> b;
	for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
		const int x = v[i].first + v[j].first;
		const int y = v[i].second + v[j].second;
		cnt += M[{x, y}]++;
	}
	cout << cnt << '\n';
}