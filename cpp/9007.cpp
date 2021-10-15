#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, x, ans = -1; cin >> x >> n;

		auto GetVec = [&]() -> vector<int> {
			vector<int> v(n), ret; ret.reserve(n * n);
			for (int i = 0; i < n; i++) cin >> v[i];
			for (int i = 0; i < n; i++) {
				int t; cin >> t;
				for (const auto& j : v) ret.push_back(t + j);
			}
			return ret;
		};

		auto v = GetVec(); sort(v.begin(), v.end());
		for (const auto& i : GetVec()) {
			auto it = lower_bound(v.begin(), v.end(), x - i);
			for (int j = -2; j <= 2; j++) {
				const int idx = it + j - v.begin();
				if (idx < 0 || idx >= v.size()) continue;
				const int val = v[idx] + i;
				if (ans == -1 || abs(x - ans) > abs(x - val) || abs(x - ans) == abs(x - val) && ans > val) ans = val;
			}
		}
		cout << ans << '\n';
	}
}