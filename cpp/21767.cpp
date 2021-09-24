#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	// input
	int n, m, k; cin >> n >> k >> m;
	vector<int> v(n), equipment(m); // target_color, equipment
	for (int i = 0; i < n; i++) cin >> v[i], --v[i];
	for (int i = 0; i < m; i++) {
		int t; cin >> t;
		for (int j = t; j --> 0;) {
			cin >> t;
			equipment[i] |= 1 << t - 1;
		}
	}

	// Get mask
	auto GetMask = [&](const int equip_state) -> int {
		int ret = 0;
		for (int i = 0; i < m; i++) {
			if (~equip_state & 1 << i) continue;
			ret |= equipment[i];
		}
		return ret;
	};

	// Get match_state
	auto GetMatchState = [&](const int equip_state, const int color, int state) -> int {
		const int mask = GetMask(equip_state);
		for (int i = 0; i < n; i++) {
			if (mask & 1 << i) continue;
			if (v[i] != color) state &= ~(1 << i);
			else state |= 1 << i;
		}
		return state;
	};

	// BFS
	vector<int> dist(1 << n + m, -1);
	queue<int> Q;
	int st_match_state = GetMatchState(0, 0, 0);
	Q.push(st_match_state << m | 0), dist[st_match_state << m | 0] = 0;
	while (Q.size()) {
		const int cur = Q.front(); Q.pop();
		const int match_state = cur >> m;
		const int equip_state = cur & (1 << m) - 1;
		if (match_state == (1 << n) - 1 && equip_state == 0) break;
		{ // 1. paint_color
			for (int i = 0; i < k; i++) {
				int nxt_match_state = GetMatchState(equip_state, i, match_state);
				int nxt_equip_state = equip_state;
				const int nxt = nxt_match_state << m | nxt_equip_state;
				if (dist[nxt] == -1) Q.push(nxt), dist[nxt] = dist[cur] + 1;
			}
		}
		{ // 2. change equipment
			for (int i = 0; i < m; i++) {
				int nxt_match_state = match_state;
				int nxt_equip_state = equip_state ^ 1 << i;
				const int nxt = nxt_match_state << m | nxt_equip_state;
				if (dist[nxt] == -1) Q.push(nxt), dist[nxt] = dist[cur] + 1;
			}
		}
	}
	cout << dist[((1 << n) - 1) << m | 0] << '\n';
}