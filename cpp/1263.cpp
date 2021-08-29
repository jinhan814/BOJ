#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int main() {
	fastio;
	int n; cin >> n;
	vector<pii> v(n);
	for (auto& [a, b] : v) cin >> b >> a;
	sort(v.rbegin(), v.rend());

	int t = v[0].first;
	for (auto& [a, b] : v) t = min(t, a) - b;
	cout << max(-1, t) << '\n';
}