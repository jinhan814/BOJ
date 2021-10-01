#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, cnt = 0; cin >> n;
	vector<int> v(n), w; bitset<100'001> check;
	for (int i = 0; i < n; i++) cin >> v[i], check[v[i]] = 1;
	for (int i = 1; i <= n << 1; i++) if (!check[i]) w.push_back(i);
	sort(v.begin(), v.begin() + n / 2);
	sort(v.begin() + n / 2, v.end());

	for (int i = 0, j = n / 2; i < n / 2 && j < n; i++) {
		while (j < n && v[i] > w[j]) j++;
		if (j < n && v[i] < w[j]) cnt++, j++;
	}
	for (int i = n - 1, j = n / 2 - 1; i >= n / 2 && j >= 0; i--) {
		while (j >= 0 && v[i] < w[j]) j--;
		if (j >= 0 && v[i] > w[j]) cnt++, j--;
	}
	cout << cnt << '\n';
}