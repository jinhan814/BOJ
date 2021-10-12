#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

int main() {
	fastio;
	int n, m, t1 = INF, t2 = INF, ans = INF; cin >> n >> m;
	while (m--) {
		int a, b; cin >> a >> b;
		t1 = min(t1, a), t2 = min(t2, b);
	}
	for (int i = 0; i * 6 <= n + 6; i++) ans = min(ans, t1 * i + t2 * max((n - 6 * i), 0));
	cout << ans << '\n';
}