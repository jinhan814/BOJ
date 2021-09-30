#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
vector<int> adj[100'001];

struct Fenwick {
	vector<int> tree; int sz;
	Fenwick(int sz = 0) : tree(sz + 1, 1), sz(sz) { Init(); }
	void Init() {
		tree[0] = 0;
		for (int i = 1; i <= sz; i++) {
			if (i + (i & -i) > sz) continue;
			tree[i + (i & -i)] += tree[i];
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
	int Kth(int k) {
		int ret = 0;
		for (int i = 20; i >= 0; i--) {
			const int t = ret + (1 << i);
			if (t <= sz && tree[t] < k) k -= tree[ret = t];
		}
		return ret + 1;
	}
} FT[100'001];

void Init() {
	for (int i = 1; i <= n; i++) {
		sort(adj[i].begin(), adj[i].end());
		adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
		FT[i] = Fenwick(adj[i].size());
	}
}

void Check(int cur) {
	for (const auto& nxt : adj[cur]) {
		const int idx = lower_bound(adj[nxt].begin(), adj[nxt].end(), cur) - adj[nxt].begin() + 1;
		FT[nxt].Update(idx, -1);
	}
}

void DFS(int cur) {
	cout << cur << ' '; Check(cur);
	for (int sz = FT[cur].Query(adj[cur].size()); sz > 0; sz = FT[cur].Query(adj[cur].size())) {
		if (sz & 1) DFS(adj[cur][FT[cur].Kth(sz + 1 >> 1) - 1]);
		else DFS(adj[cur][FT[cur].Kth(1) - 1]);
	}
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		if (a == b) continue;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	Init(); DFS(1);
}