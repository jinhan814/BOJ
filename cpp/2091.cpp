#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int x, a, b, c, d; cin >> x >> a >> b >> c >> d;
	c = min(c, 1000), d = min(d, 400);

	int ans[4]{}, mx = -1;
	for (int cnt_c = 0; cnt_c <= c; cnt_c++) for (int cnt_d = 0; cnt_d <= d; cnt_d++) {
		const int rem = x - 10 * cnt_c - 25 * cnt_d;
		const int cnt_b = (rem - min(a, rem) + 4) / 5;
		const int cnt_a = rem - 5 * cnt_b;
		const int cnt = cnt_a + cnt_b + cnt_c + cnt_d;
		if (0 <= cnt_a && cnt_a <= a && 0 <= cnt_b && cnt_b <= b && cnt_a + 5 * cnt_b == rem && mx < cnt) {
			ans[0] = cnt_a; ans[1] = cnt_b;
			ans[2] = cnt_c; ans[3] = cnt_d;
			mx = cnt;
		}
	}

	for (int i = 0; i < 4; i++) cout << ans[i] << ' ';
	cout << '\n';
}