#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

int n, v[100'000], cnt[100'001];

ll Sol() {
	ll ret = 0;
	for (int l = 0, r = -1; l < n; cnt[v[l++]]--) {
		while (r + 1 < n && !cnt[v[r + 1]]) cnt[v[++r]]++;
		ret += r - l + 1;
	}
	return ret;
}

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << Sol() << '\n';
}