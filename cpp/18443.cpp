#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

const int INF = int(1e18) + 7;
int n, m, L, mn = INF, v[100];
int pSum[100], DP[100][101], Log[100][101];
vector<int> ans;

int32_t main() {
	fastio;
	cin >> n >> m >> L;
	deque<int> DQ(n);
	for (int i = 0; i < n; i++) cin >> DQ[i];

	for (int c = 0; c < n; c++, DQ.push_back(DQ.front()), DQ.pop_front()) {
		// pre-processing
		memset(pSum, 0, sizeof pSum);
		memset(DP, -1, sizeof DP);
		memset(Log, -1, sizeof Log);
		for (int i = 1, sum = 0; i < n; i++) {
			const int delta = DQ[i] >= DQ[i - 1] ? DQ[i] - DQ[i - 1] : L + DQ[i] - DQ[i - 1];
			v[i] = sum += delta;
			pSum[i] = pSum[i - 1] + v[i];
		}

		// DP
		auto Cost = [&](int l, int r) -> int {
			int mid = l + r >> 1;
			const int t1 = v[mid] * (mid - l) - ((mid ? pSum[mid - 1] : 0) - (l ? pSum[l - 1] : 0));
			const int t2 = (pSum[r] - pSum[mid]) - v[mid] * (r - mid);
			return t1 + t2;
		};
		auto DFS = [&](int pos, int cnt, auto&& DFS) ->int {
			if (pos == n) return cnt ? INF : 0;
			if (cnt == 0) return INF;
			int& ret = DP[pos][cnt];
			if (ret != -1) return ret; ret = INF;
			for (int i = pos; i < n; i++) {
				const int t = DFS(i + 1, cnt - 1, DFS);
				if (t == INF) continue;
				const int cost = Cost(pos, i);
				if (ret > t + cost) ret = t + cost, Log[pos][cnt] = i + 1;
			}
			return ret;
		};

		// tracking
		auto res = DFS(0, m, DFS);
		if (mn > res) {
			mn = res; ans.clear();
			for (int i = 0, cnt = m; cnt > 0; cnt--) {
				ans.push_back(DQ[i + Log[i][cnt] - 1 >> 1]);
				i = Log[i][cnt];
			}
			sort(ans.begin(), ans.end());
		}
	}

	cout << mn << '\n';
	for (const auto& i : ans) cout << i << ' ';
	cout << '\n';
}