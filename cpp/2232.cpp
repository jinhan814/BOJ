#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, v[50'000];

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 0; i < n; i++) {
		if (i && v[i - 1] > v[i]) continue;
		if (i + 1 < n && v[i] < v[i + 1]) continue;
		cout << i + 1 << '\n';
	}
}