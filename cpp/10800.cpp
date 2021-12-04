#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int n, res[200'001], pSum1[200'001];
vector<int> v, w[200'001], pSum2[200'001];
vector<pii> p;

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b; --a;
		v.push_back(b), w[a].push_back(b);
		p.push_back({ a, b });
	}

	sort(v.begin(), v.end());
	for (int i = 0; i < n; i++) {
		sort(w[i].begin(), w[i].end());
		pSum1[i + 1] = pSum1[i] + v[i];
		pSum2[i].resize(w[i].size() + 1);
		for (int j = 0; j < w[i].size(); j++)
			pSum2[i][j + 1] = pSum2[i][j] + w[i][j];
	}

	for (const auto& [a, b] : p) {
		auto t1 = lower_bound(v.begin(), v.end(), b) - v.begin();
		auto t2 = lower_bound(w[a].begin(), w[a].end(), b) - w[a].begin();
		cout << pSum1[t1] - pSum2[a][t2] << '\n';
	}
}