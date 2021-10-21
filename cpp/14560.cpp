#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	int D; cin >> D;

	if (n == 1) return !(cout << (v[0] <= D ? 3 : 1) << '\n');

	auto F = [&](int l, int r) -> vector<int> {
		auto DFS = [&](int pos, auto&& DFS) -> vector<int> {
			if (pos > r) return { 0 };
			auto v1 = DFS(pos + 1, DFS), v2 = v1, v3 = v2;
			for (auto& i : v2) i -= v[pos];
			for (auto& i : v3) i += v[pos];
			vector<int> ret; ret.reserve(v1.size() + v2.size() + v3.size());
			for (int i1 = 0, i2 = 0, i3 = 0; i1 < v1.size() || i2 < v2.size() || i3 < v3.size();) {
				if (i1 < v1.size()
					&& (i2 == v2.size() || v1[i1] <= v2[i2])
					&& (i3 == v3.size() || v1[i1] <= v3[i3])) ret.push_back(v1[i1++]);
				if (i2 < v2.size()
					&& (i1 == v1.size() || v2[i2] <= v1[i1])
					&& (i3 == v3.size() || v2[i2] <= v3[i3])) ret.push_back(v2[i2++]);
				if (i3 < v3.size()
					&& (i1 == v1.size() || v3[i3] <= v1[i1])
					&& (i2 == v2.size() || v3[i3] <= v2[i2])) ret.push_back(v3[i3++]);
			}
			return ret;
		};
		return DFS(l, DFS);
	};
	auto A = F(0, n / 2 - 1), B = F(n / 2, n - 1);

	int ans = 0;
	for (int i = 0, l = 0, r = 0; i < A.size(); i++) {
		while (r < B.size() && B[r] <= A[i] + D) r++;
		while (l < B.size() && B[l] < A[i] - D) l++;
		ans += r - l;
	}
	cout << ans << '\n';
}