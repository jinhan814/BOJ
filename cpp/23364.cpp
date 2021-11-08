#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n); map<int, int> M;
	for (int i = 0; i < n; i++) cin >> v[i], M[v[i]] = i + 1;
	sort(v.begin(), v.end());
	for (int i = 0; i < n; i++) {
		for (int j = 2; ; j++) {
			auto it = lower_bound(v.begin() + i + 1, v.end(), v[i] * j);
			if (it == v.end()) break;
			if (*it != v[i] * j) continue;
			return cout << M[v[i]] << ' ' << M[*it] << '\n', 0;
		}
	}
}