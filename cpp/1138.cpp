#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n), w(n); iota(v.begin(), v.end(), 0);
	for (int i = 0; i < n; i++) cin >> w[i];
	do {
		vector<int> t(n);
		for (int i = 0; i < n; i++) for (int j = 0; j < i; j++)
			if (v[j] > v[i]) t[v[i]]++;
		if (t == w) for (int i = 0; i < n; i++) cout << v[i] + 1 << ' ';
	} while (next_permutation(v.begin(), v.end()));
	cout << '\n';
}