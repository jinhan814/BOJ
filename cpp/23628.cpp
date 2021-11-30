#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n = []() -> int {
		int y1, m1, d1; cin >> y1 >> m1 >> d1;
		int y2, m2, d2; cin >> y2 >> m2 >> d2;
		return (y2 - y1) * 360 + (m2 - m1) * 30 + (d2 - d1);
	}();

	auto Sol1 = [](int n) -> int {
		const int y = n / 360;
		const int t = y / 2;
		return 15 * y + t * (t - 1) / 2 * 2 + (y & 1 ? y / 2 : 0);
	};

	auto Sol2 = [](int n) -> int {
		return min(36, n / 30);
	};

	cout << Sol1(n) << ' ' << Sol2(n) << '\n';
	cout << n << "days" << '\n';
}