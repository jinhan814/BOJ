#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, v[100'001], indegree[100'001];
bitset<100'001> visited;
vector<int> res;

int main() {
	fastio;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> v[i], indegree[v[i]]++;

	queue<int> Q;
	for (int i = 2; i <= n; i++) if (!indegree[i]) Q.push(i);

	for (int cur = 1; !visited[cur];) {
		visited[cur] = 1;
		res.push_back(cur = v[cur]);
	}

	for (; Q.size(); Q.pop()) {
		for (auto cur = Q.front(); ;) {
			res.push_back(cur);
			if (visited[cur]) break;
			visited[cur] = 1, cur = v[cur];
		}
	}

	for (int i = 1; i <= n; i++) {
		if (visited[i]) continue;
		for (int cur = i; ;) {
			res.push_back(cur);
			if (visited[cur]) break;
			visited[cur] = 1, cur = v[cur];
		}
	}

	cout << res.size() << '\n';
	for (const auto& i : res) cout << i << ' '; cout << '\n';
}