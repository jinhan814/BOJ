#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

/* Mo's Algorithm */

using ll = long long;

class Query { // reference : https://www.acmicpc.net/source/27941653
public:
	int idx, st, en, lca;
	Query(int idx, int st, int en, int lca) : idx(idx), st(st), en(en), lca(lca) {}
	bool operator< (const Query& i) const { return pr < i.pr; }

private:
	ll pr = ConvHilbert(st, en);
	static ll ConvHilbert(int x, int y) {
		ll ret = 0;
		for (int i = 17, cx, cy; ~i; i--) {
			cx = x >> i & 1, cy = y >> i & 1;
			ret = ret << 2 | cx << 1 | cx ^ cy;
			cy || (swap(x, y), cx) && (x = ~x, y = ~y);
		}
		return ret;
	}
};

/* Main */

int n, q, v[100'001], res[100'001];
int dep[100'001], sz[100'001];
int par[100'001], top[100'001]{ 0, 1 };
int in[100'001], out[100'001];
vector<int> I, E, adj[100'001];
vector<Query> Q;

int DFS1(int cur, int prv) {
	int& ret = sz[cur] = 1;
	for (auto& nxt : adj[cur]) {
		if (nxt == prv) continue;
		dep[nxt] = dep[cur] + 1, par[nxt] = cur;
		ret += DFS1(nxt, cur);
		if (sz[adj[cur][0]] < sz[nxt]) swap(adj[cur][0], nxt);
	}
	return ret;
}

void DFS2(int cur) {
	in[cur] = E.size(), E.push_back(cur);
	for (const auto& nxt : adj[cur]) {
		if (nxt == par[cur]) continue;
		top[nxt] = nxt == adj[cur][0] ? top[cur] : nxt;
		DFS2(nxt);
	}
	out[cur] = E.size(), E.push_back(cur);
}

int LCA(int a, int b) {
	for (; top[a] ^ top[b]; a = par[top[a]])
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
    return dep[a] < dep[b] ? a : b;
}

int main() {
	fastio;
	// 1. input & coordinate compression
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> v[i], I.push_back(v[i]);
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	sort(I.begin(), I.end()), I.erase(unique(I.begin(), I.end()), I.end());
	for (int i = 1; i <= n; i++) v[i] = lower_bound(I.begin(), I.end(), v[i]) - I.begin();

	// 2. precalc for ett, lca
	DFS1(1, -1), DFS2(1);

	// 3. query
	int q; cin >> q;
	for (int i = 1; i <= q; i++) {
		int a, b; cin >> a >> b;
		if (in[a] > in[b]) swap(a, b);
		const int lca = LCA(a, b);
		if (a == lca) Q.push_back(Query(i, in[a], in[b], -1));
		else Q.push_back(Query(i, out[a], in[b], lca));
	}
	sort(Q.begin(), Q.end());

	// 4. mo's algorithm
	bitset<100'001> check; vector<int> t(n + 1);
	int st = Q[0].st, en = st - 1, cnt = 0;
	auto Update = [&](int idx) {
		check[E[idx]].flip();
		if (check[E[idx]]) { if (!t[v[E[idx]]]++) cnt++; }
		else if (!--t[v[E[idx]]]) cnt--;
	};
	for (int i = 0; i < Q.size(); i++) {
		while (Q[i].st < st) Update(--st);
		while (Q[i].st > st) Update(st++);
		while (Q[i].en > en) Update(++en);
		while (Q[i].en < en) Update(en--);
		res[Q[i].idx] = cnt;
		if (Q[i].lca != -1 && !t[v[Q[i].lca]]) res[Q[i].idx]++;
	}
	for (int i = 1; i <= q; i++) cout << res[i] << '\n';
}