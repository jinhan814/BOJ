#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

template<size_t sz = 1 << 17>
struct SegTree {
	vector<int> tree, lazy;
	SegTree() : tree(sz << 1, INF), lazy(sz << 1) {}
	void Propagate(int node, int nodeL, int nodeR) {
		if (lazy[node]) {
			if (node < sz) {
				lazy[node << 1] += lazy[node];
				lazy[node << 1 | 1] += lazy[node];
			}
			tree[node] += lazy[node];
			lazy[node] = 0;
		}
	}
	void Update(int L, int R, int val, int node = 1, int nodeL = 1, int nodeR = sz) {
		Propagate(node, nodeL, nodeR);
		if (R < nodeL || nodeR < L) return;
		if (L <= nodeL && nodeR <= R) {
			lazy[node] += val;
			Propagate(node, nodeL, nodeR);
			return;
		}
		int mid = nodeL + nodeR >> 1;
		Update(L, R, val, node << 1, nodeL, mid);
		Update(L, R, val, node << 1 | 1, mid + 1, nodeR);
		tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
	}
	int Query(int L, int R, int node = 1, int nodeL = 1, int nodeR = sz) {
		Propagate(node, nodeL, nodeR);
		if (R < nodeL || nodeR < L) return INF;
		if (L <= nodeL && nodeR <= R) return tree[node];
		int mid = nodeL + nodeR >> 1;
		return min(Query(L, R, node << 1, nodeL, mid), Query(L, R, node << 1 | 1, mid + 1, nodeR));
	}
};

SegTree ST;

int main() {
	fastio;
	string s; cin >> s;
	int n = s.size();
	for (int i = 1, t = 0, pSum = 0; i <= n; i++, pSum += t) {
		t += s[i - 1] == '(' ? 1 : -1;
		ST.Update(i, i, t - INF);
	}

	int q, ans = 0; cin >> q;
	while (q--) {
		int t; cin >> t;
		if (s[t - 1] == '(') ST.Update(t, n, -2), s[t - 1] = ')';
		else ST.Update(t, n, 2), s[t - 1] = '(';
		if (ST.Query(n, n) == 0 && ST.Query(1, n) >= 0) ans++;
	}
	cout << ans << '\n';
}