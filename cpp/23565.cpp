#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

ll Sol(ll a, ll b, ll c, ll d) {
	ll res = !!a << 3 | !!b << 2 | !!c << 1 | !!d;
	ll sum = a + 2 * b + 3 * c + 4 * d;
	if ((res & -res) == res) return a + b + c + d + 1;
	if (res > 11) return -~sum;
	if (res == 3) return c < 3 ? -~c * -~d : d < 2 ? 2 * -~c : sum - 5;
	if (res == 5) return b + 2 * d + 1;
	if (res == 6) return b < 2 ? 2 * -~c : ~-sum;
	if (res == 7) return ~-sum;
	if (res == 9) return a < 3 ? -~a * -~d : -~sum;
	if (res == 10) return a < 2 ? 2 * -~c : -~sum;
	return a < 2 ? c < 2 ? 3 * d + 4 : ~-sum : -~sum;
}

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		ll a, b, c, d; cin >> a >> b >> c >> d;
		cout << Sol(a, b, c, d) << '\n';
	}
}