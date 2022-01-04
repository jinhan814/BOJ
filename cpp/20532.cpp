#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

int n, v[100'000], cnt1[100'001], cnt2[100'001];
vector<int> adj[100'000], fac[100'001];

ll DFS(int cur) {
	ll ret = cnt2[v[cur]] - cnt1[v[cur]];
	for (const auto& d : fac[v[cur]]) ret += cnt1[d];
	for (const auto& d : fac[v[cur]]) cnt2[d]++; cnt1[v[cur]]++;
	for (const auto& nxt : adj[cur]) ret += DFS(nxt);
	for (const auto& d : fac[v[cur]]) cnt2[d]--; cnt1[v[cur]]--;
	return ret;
}

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 1; i < n; i++) {
		int t; cin >> t; --t;
		adj[t].push_back(i);
	}
	for (int i = 1; i <= 100'000; i++) {
		for (int j = 1; i * j <= 100'000; j++)
			fac[i * j].push_back(i);
	}
	cout << DFS(0) << '\n';
}