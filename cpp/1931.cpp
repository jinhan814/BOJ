#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int main() {
	fastio;
	int n, cnt = 0; cin >> n;
	vector<pii> v(n);
	for (auto& [a, b] : v) cin >> a >> b;
	sort(v.begin(), v.end(), [](const pii& a, const pii& b) {
		return a.second < b.second || a.second == b.second && a.first < b.first;
	});
	for (int i = 0, t = 0; i < n; i++) {
		if (v[i].first < t) continue;
		t = v[i].second, cnt++;
	}
	cout << cnt << '\n';
}