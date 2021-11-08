#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

template<size_t sz>
struct Fenwick {
	int tree[sz + 1]{};
	void Init() {
		for (int i = 1; i <= sz; i++) {
			tree[i]++;
			if (i + (i & -i) <= sz) tree[i + (i & -i)] += tree[i];
		}
	}
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
	int n, pos[100'001]; cin >> n;
	Fenwick<100'000> FT; FT.Init();
	for (int i = 1, t; i <= n; i++) cin >> t, pos[t] = i;
	for (int i = 1, j = 0; j < n; j++) {
		FT.Update(pos[i], -1);
		cout << (j & 1 ? FT.Query(n) - FT.Query(pos[i]) : FT.Query(pos[i])) << '\n';
		i = i <= n + 1 >> 1 ? n + 1 - i : n + 2 - i;
	}
}