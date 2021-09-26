#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	for (int c = 1; c <= N; c++) {
		int n, m, ans = 1e9; cin >> n >> m;
		vector<int> v(m);
		for (auto& i : v) cin >> i;
		sort(v.begin(), v.end());

		do {
			int cur = 0; bitset<101> check; check.set();
			for (const auto& cmd : v) {
				int l = cmd, r = cmd;
				while (l > 1 && check[l - 1]) l--;
				while (r < n && check[r + 1]) r++;
				check[cmd] = 0; cur += r - l;
			}
			ans = min(ans, cur);
		} while (next_permutation(v.begin(), v.end()));
		cout << "Case #" << c << ": " << ans << '\n';
	}
}