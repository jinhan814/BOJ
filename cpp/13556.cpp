#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 5'000'000;

template<size_t sz>
struct Fenwick {
	int tree[sz + 1]{};
	void Update(int i, int val) {
		if (val < 0) val += MOD;
		for (; i <= sz; i += i & -i) if ((tree[i] += val) >= MOD) tree[i] -= MOD;
	}
	int Query(int i) {
		int ret = 0;
		for (; i; i -= i & -i) if ((ret += tree[i]) >= MOD) ret -= MOD;
		return ret;
	}
};

Fenwick<100'000> FT[50];
bitset<100'001> check;
int n, k, v[100'001], t[50][100'001];

int main() {
	fastio;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
		for (int j = k - 1; j; j--) {
			FT[j].Update(v[i], FT[j - 1].Query(v[i] - 1) - t[j - 1][v[i]]);
			t[j][v[i]] = FT[j].Query(v[i] - 1);
		}
		FT[0].Update(v[i], !check[v[i]]); check[v[i]] = 1;
		t[0][v[i]] = FT[0].Query(v[i] - 1);
	}
	cout << FT[k - 1].Query(100'000) << '\n';
}