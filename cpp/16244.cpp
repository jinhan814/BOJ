#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int64_t n, sum = 0; cin >> n; int v[n];
	for (auto& i : v) cin >> i, sum += i;
	for (int i = 0, flag = 0; i < n; i++) {
		if (v[i] << 1 ^ sum || flag) cout << v[i] << ' ';
		else flag = 1;
	}
	cout << (sum >> 1) << '\n';
}