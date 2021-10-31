#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
	fastio;
	int N, K, M; cin >> N >> K >> M;

	auto Check = [&](const int X) -> bool {
		int G = 0, cnt = K;
		while (G < N && cnt) {
			const int Y = (N - G) / X;
			if (Y <= M) { G += M * cnt; break; }
			const int t = min((N - X * Y - G) / Y + 1, cnt);
			G += Y * t, cnt -= t;
		}
		return G >= N;
	};

	int lo = 1, hi = N + 1;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (Check(mid)) lo = mid;
		else hi = mid;
	}
	cout << lo << '\n';
}