#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
using i64 = long long;

int n, m, I[300'001];
i64 val[300'001];
vector<pii> adj[300'001];
priority_queue<i64> PQ[300'001];

void DFS(int cur, int prv) {
	int cnt = 0;
	for (const auto& [nxt, c] : adj[cur]) {
		if (nxt == prv) continue;
		DFS(nxt, cur);
		if (PQ[I[nxt]].empty()) {
			PQ[I[nxt]].push(c);
			PQ[I[nxt]].push(c);
		}
		else {
			i64 optr = PQ[I[nxt]].top(); PQ[I[nxt]].pop();
			i64 optl = PQ[I[nxt]].top(); PQ[I[nxt]].pop();
			PQ[I[nxt]].push(optl + c);
			PQ[I[nxt]].push(optr + c);
		}
		val[cur] += val[nxt] + c; cnt++;
		if (PQ[I[cur]].size() < PQ[I[nxt]].size()) swap(I[cur], I[nxt]);
		while (PQ[I[nxt]].size()) PQ[I[cur]].push(PQ[I[nxt]].top()), PQ[I[nxt]].pop();
	}
	for (int i = 1; i < cnt; i++) PQ[I[cur]].pop();
}

i64 Calc() {
	vector<i64> v;
	while (PQ[I[1]].size()) v.push_back(PQ[I[1]].top()), PQ[I[1]].pop();
	for (int i = v.size() - 1; i >= 0; i--) {
		const i64 m = -i;
		const i64 d = v[i] - (i + 1 < v.size() ? v[i + 1] : 0);
		val[1] += m * d;
	}
	return val[1];
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 2; i <= n + m; i++) {
		int a, b; cin >> a >> b;
		adj[i].push_back({ a, b });
		adj[a].push_back({ i, b });
	}
	iota(I + 1, I + n + m + 1, 1); DFS(1, -1);
	cout << Calc() << '\n';
}