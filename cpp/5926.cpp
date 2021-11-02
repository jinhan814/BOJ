#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define all(v) (v).begin(), (v).end()
#define Compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())
#define IDX(v, x) (lower_bound(all(v), x) - (v).begin())

int main() {
	fastio;
	int n; cin >> n;
	vector<pair<int, int>> v(n); vector<int> I;
	for (auto& [a, b] : v) cin >> a >> b, I.push_back(b); Compress(I);
	for (auto& [a, b] : v) b = IDX(I, b);
	sort(v.begin(), v.end());

	vector<int> cnt(I.size()); int cur = 0;
	auto Push = [&](int t) { if (!cnt[t]++) cur++; };
	auto Pop = [&](int t) { if (!--cnt[t]) cur--; };

	int mn = 1e9;
	for (int l = 0, r = 0; r < n; r++) {
		Push(v[r].second);
		while (cur == I.size()) {
			mn = min(mn, v[r].first - v[l].first);
			Pop(v[l++].second);
		}
	}
	cout << mn << '\n';
}