#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, indeg[200];
double DP[200];
map<string, int> M;
vector<int> adj[200];
bitset<200> visited;

void DFS(int cur) {
	visited[cur] = 1;
	for (const auto& nxt : adj[cur]) {
		indeg[nxt]++;
		if (!visited[nxt]) DFS(nxt);
	}
}

int main() {
	fastio;
	// 1. input
	cin >> n >> m;
	string s; cin >> s;
	M[s] = M.size();
	while (n--) {
		string a, b, c; cin >> a >> b >> c;
		if (!M.count(a)) M[a] = M.size();
		if (!M.count(b)) M[b] = M.size();
		if (!M.count(c)) M[c] = M.size();
		adj[M[b]].push_back(M[a]);
		adj[M[c]].push_back(M[a]);
	}

	// 2. topological sort
	DFS(M[s]);
	queue<int> Q; Q.push(M[s]); DP[M[s]] = 1;
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		for (const auto& nxt : adj[cur]) {
			DP[nxt] += DP[cur] / 2;
			if (!--indeg[nxt]) Q.push(nxt);
		}
	}

	// 3. find mx
	double mx = -1; string res;
	while (m--) {
		string s; cin >> s;
		if (!M.count(s)) continue;
		if (mx < DP[M[s]]) mx = DP[M[s]], res = s;
	}
	cout << res << '\n';
}