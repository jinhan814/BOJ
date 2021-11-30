#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	for (int n; cin >> n;) {
		vector<int> v(n), inv(n + 1);
		for (int i = 0; i < n; i++) cin >> v[i];
		for (int i = 0; i < n; i++) { int t; cin >> t; inv[t] = i; }
		int cnt = 0;
		for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++)
			if (inv[v[i]] > inv[v[j]]) cnt++;
		cout << cnt << '\n';
	}
}