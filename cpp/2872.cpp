#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, cnt, v[300'000];

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = n, t = n; i-- > 0;)
		if (v[i] == t) cnt++, t--;
	cout << n - cnt << '\n';
}