#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

ll Sol(const vector<ll>& v) {
	ll ret = 0;
	for (int i = 0, j = 0; i < v.size(); i = j) {
		while (j < v.size() && v[i] == v[j]) j++;
		ret += (ll)(j - i) * (j - i - 1) >> 1;
	}
	return ret;
}

int main() {
	fastio;
	int n, k; cin >> n >> k;
	vector<ll> v(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
		v[i] += v[i - 1] - k;
	}
	sort(v.begin(), v.end());
	cout << Sol(v) << '\n';
}