#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

vector<int> v;
int dist[1'000'001], prv[1'000'001];

void Init() {
	auto F = [&](int sz) -> void {
		for (int i = 0; i < 1 << sz; i++) {
			int cur = 0;
			for (int j = 0; j < sz; j++) cur = cur * 10 + (i & 1 << j ? 7 : 4);
			v.push_back(cur);
		}
	};
	for (int i = 1; i <= 6; i++) F(i);
	sort(v.begin(), v.end());
}

int main() {
	fastio;
	memset(dist, -1, sizeof dist), memset(prv, -1, sizeof prv);
	queue<int> Q; dist[0] = 0, Q.push(0); Init();
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		for (const auto& i : v) {
			const auto nxt = cur + i;
			if (nxt > 1'000'000) continue;
			if (dist[nxt] == -1) dist[nxt] = dist[cur] + 1, prv[nxt] = cur, Q.push(nxt);
		}
	}

	int n; cin >> n;
	if (dist[n] == -1) cout << -1 << '\n';
	else {
		vector<int> res;
		for (int i = n; i; i = prv[i]) res.push_back(i - prv[i]);
		sort(res.begin(), res.end());
		for (auto& i : res) cout << i << ' '; cout << '\n';
	}
}