#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct State {
	vector<int> v;
	State(int n) : v(n) {}
	int operator() () {
		int ret = 0;
		for (auto& i : v) ret = ret * 5 + i;
		return ret;
	}
	bool Check() {
		for (auto& i : v) if (i != v[0]) return 0;
		return 1;
	}
	void Flip(const vector<int>& adj, int k) {
		for (auto& i : adj) v[i] = (v[i] + k) % 5;
	}
};

int main() {
	fastio;
	int n, k; cin >> n >> k;
	State S(n); vector<vector<int>> adj(k);
	for (int i = 0; i < n; i++) cin >> S.v[i];
	for (int i = 0; i < k; i++) {
		int t; cin >> t; adj[i].resize(t);
		for (auto& j : adj[i]) cin >> j, --j;
	}

	auto Sol = [&]() -> int {
		int sz = 1;
		for (int i = 0; i < n; i++) sz *= 5;
		vector<int> dist(sz, -1); queue<State> Q;
		Q.push(S); dist[S()] = 0;
		while (Q.size()) {
			auto cur = Q.front(); Q.pop();
			if (cur.Check()) return dist[cur()];
			for (int i = 0; i < k; i++) {
				auto nxt = cur; nxt.Flip(adj[i], i + 1);
				if (!~dist[nxt()]) Q.push(nxt), dist[nxt()] = dist[cur()] + 1;
			}
		}
		return -1;
	};
	cout << Sol() << '\n';
}