#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bitset<1 << 17> B;

bool Sol(const vector<int>& v) {
	const int n = v.size();
	if (n > 1000) return 1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (B[v[i] ^ v[j]]) return 1;
		}
		for (int j = 0; j < i; j++) B[v[i] ^ v[j]] = 1;
	}
	return 0;
}

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << (Sol(v) ? "Yes" : "No") << '\n';
}