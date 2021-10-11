#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int n, v[100'000], cnt[100'000], pos[100'000];

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i];

	stack<pii> S; memset(pos, -1, sizeof pos);
	for (int i = 0; i < n; i++) {
		while (S.size() && S.top().first <= v[i]) S.pop();
		if (S.size()) {
			cnt[i] += S.size();
			const int d1 = abs(pos[i] - i), d2 = abs(S.top().second - i);
			if (pos[i] == -1 || d1 > d2 || d1 == d2 && pos[i] > S.top().second) pos[i] = S.top().second;
		}
		S.push({ v[i], i });
	}

	while (S.size()) S.pop();
	for (int i = n - 1; i >= 0; i--) {
		while (S.size() && S.top().first <= v[i]) S.pop();
		if (S.size()) {
			cnt[i] += S.size();
			const int d1 = abs(pos[i] - i), d2 = abs(S.top().second - i);
			if (pos[i] == -1 || d1 > d2 || d1 == d2 && pos[i] > S.top().second) pos[i] = S.top().second;
		}
		S.push({ v[i], i });
	}

	for (int i = 0; i < n; i++) {
		if (cnt[i]) cout << cnt[i] << ' ' << pos[i] + 1 << '\n';
		else cout << 0 << '\n';
	}
}