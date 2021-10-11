#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, ans = 0; cin >> n;
	vector<pair<int, int>> v(n);
	for (auto& [x, y] : v) cin >> x >> y;
	sort(v.begin(), v.end());

	stack<int> S;
	for (const auto& [_, val] : v) {
		while (S.size() && S.top() > val) S.pop();
		if (val && (S.empty() || S.top() < val)) S.push(val), ans++;
	}
	cout << ans << '\n';
}