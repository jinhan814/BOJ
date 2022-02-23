#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int Conv(char a, char b) {
    if (a > b) swap(a, b);
    if (a == b) return a == 'I' ? 0 : a == 'N' ? 1 : 2;
    return a == 'I' ? b == 'N' ? 3 : 4 : 5;
}

int main() {
	fastio;
	int n, v[6]{}; cin >> n;
	while (n--) {
		char a, b; int t; cin >> a >> b >> t;
		v[Conv(a, b)] += t;
	}
	if (!v[3] + !v[4] + !v[5] < 2) cout << reduce(v, v + 6);
	else if (v[3]) cout << max(v[0] + v[1] + v[3], v[2]);
	else if (v[4]) cout << max(v[0] + v[2] + v[4], v[1]);
	else if (v[5]) cout << max(v[1] + v[2] + v[5], v[0]);
	else cout << max({ v[0], v[1], v[2] });
}