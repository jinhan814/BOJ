#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int16_t N, v[200'000]; cin >> N;
	while (N--) {
		int n, m, k, ans = 0; cin >> n >> m >> k;
		for (int i = 0; i < n; i++) cin >> v[i];
		for (int i = n; i < n + m - 1; i++) v[i] = v[i - n];
		if (m < n) for (int i = 0, sum = 0; i < n + m - 1; i++) {
			sum += v[i];
			if (i - m >= 0) sum -= v[i - m];
			if (i >= m - 1 && sum < k) ans++;
		}
		else ans = accumulate(v, v + n, 0) < k;
		cout << ans << '\n';
	}
}