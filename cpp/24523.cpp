#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, v[1'000'001]; cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = n - 1; i >= 0; i--) {
		if (i + 1 < n && v[i] == v[i + 1]) v[i + 1] = v[i + 2];
		else v[i + 1] = i + 1;
	}
	for (int i = 1; i <= n; i++) {
        if (v[i] == n) cout << -1 << ' ';
        else cout << v[i] + 1 << ' ';
    }
}