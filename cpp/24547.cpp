#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int sq = 400;
using i64 = long long;

template<typename T, size_t sz = 100'000>
struct Fenwick {
	T tree[sz + 1];
	void Update(int i, T val) {
		for (; i <= sz; i += i & -i) tree[i] += val;
	}
	T Query(int i) {
		if (i < 0) return 0;
		if (i > sz) i = sz;
		T ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
};

int n, q, v[100'001];
i64 res[sq + 1];
Fenwick<i64> FT1;
Fenwick<int> FT2;

void Push(const int i) {
	FT1.Update(v[i], v[i]);
	FT2.Update(v[i], 1);
	for (int j = 1; j <= sq; j++) res[j] += v[i] / j;
}

void Pop(const int i) {
	FT1.Update(v[i], -v[i]);
	FT2.Update(v[i], -1);
	for (int j = 1; j <= sq; j++) res[j] -= v[i] / j;
}

i64 Query1(const int x) {
	if (x <= sq) return FT1.Query(100'000) - x * res[x];
	i64 ret = FT1.Query(100'000);
	for (i64 i = 1; i * x <= 100'000; i++) {
		const int t = FT2.Query((i + 1) * x - 1) - FT2.Query(i * x - 1);
		ret -= i * t * x;
	}
	return ret;
}

i64 Query2(const int x) {
	i64 ret = (i64)n * x;
	for (int i = 1, j; i <= x; i = j + 1) {
		const int q = x / i; j = x / q;
		ret -= q * (FT1.Query(j) - FT1.Query(i - 1));
	}
	return ret;
}

int main() {
	fastio;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> v[i], Push(i);
	cin >> q;
	while (q--) {
		int t, a, b; cin >> t >> a;
		if (t == 1) cout << Query1(a) << '\n';
		else if (t == 2) cout << Query2(a) << '\n';
		else cin >> b, Pop(a), v[a] = b, Push(a);
	}
}