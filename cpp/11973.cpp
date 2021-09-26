#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, k, v[50'000];

inline bool Check(const int mid) {
	int cnt = 0;
	for (int i = 0; i < n;) {
		const int j = i;
		while (i < n && v[i] - v[j] <= mid << 1) i++;
		cnt++;
	}
	return cnt <= k;
}

int main() {
	fastio;
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v, v + n);

	int lo = -1, hi = 1e9;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (!Check(mid)) lo = mid;
		else hi = mid;
	}
	cout << hi << '\n';
}