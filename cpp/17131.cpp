#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define all(v) (v).begin(), (v).end()
#define Compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())
#define IDX(v, x) (lower_bound(all(v), x) - (v).begin() + 1)

constexpr int MOD = 1e9 + 7;
using pii = pair<int, int>;

template<size_t sz>
struct Fenwick {
	int tree[sz + 1]{};
	void Update(int i, int val) {
		for (; i <= sz; i += i & -i) if ((tree[i] += val) >= MOD) tree[i] -= MOD;
	}
	int Query(int i) {
		int ret = 0;
		for (; i; i -= i & -i) if ((ret += tree[i]) >= MOD) ret -= MOD;
		return ret;
	}
};

int main() {
	fastio;
	int n, ans = 0; cin >> n;
	vector<pii> v(n); vector<int> I;
	for (auto& [x, y] : v) cin >> x >> y, I.push_back(y); Compress(I);
	for (auto& [x, y] : v) y = IDX(I, y); sort(v.begin(), v.end());

	Fenwick<200'000> FT1, FT2;
	for (int i = 0, j = 0; i < n;) {
		for (; j < n && v[i].first == v[j].first; j++) {
			const auto& [x, y] = v[j];
			if ((ans += FT2.Query(y - 1)) >= MOD) ans -= MOD;
		}
		for (; i < j; i++) {
			const auto& [x, y] = v[i];
			FT2.Update(y, i - FT1.Query(y));
			FT1.Update(y, 1);
		}
	}
	cout << ans << '\n';
}