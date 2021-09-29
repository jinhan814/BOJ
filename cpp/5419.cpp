#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define all(v) (v).begin(), (v).end()
#define compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())

using pii = pair<int, int>;

struct Fenwick {
	vector<int> tree; int sz;
	Fenwick(int sz) : tree(sz + 1), sz(sz) {}
	void Update(int i, int val) {
		for (; i <= sz; i += i & -i) tree[i] += val;
	}
	int Query(int i) {
		int ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
};

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		vector<pii> v(n); vector<int> I;
		for (auto& [a, b] : v) cin >> a >> b, I.push_back(a);

		compress(I);
		for (auto& [a, b] : v) a = lower_bound(all(I), a) - I.begin() + 1;
		sort(v.begin(), v.end(), [](const pii& a, const pii& b) {
			return a.second ^ b.second ? a.second > b.second : a.first < b.first;
		});

		int64_t ans = 0; Fenwick FT(I.size());
		for (const auto& [a, b] : v) {
			ans += FT.Query(a);
			FT.Update(a, 1);
		}
		cout << ans << '\n';
	}
}