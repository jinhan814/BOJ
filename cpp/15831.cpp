#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, a, b, ans = 0; cin >> n >> a >> b;
	string s; cin >> s;
	for (int l = 0, r = 0, t1 = 0, t2 = 0; r < n; r++) {
		(s[r] == 'B' ? t1 : t2)++;
		while (t1 > a) (s[l++] == 'B' ? t1 : t2)--;
		if (t1 <= a && t2 >= b) ans = max(ans, r - l + 1);
	}
	cout << ans << '\n';
}