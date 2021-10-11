#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Info { int year, a, b; };

int main() {
	fastio;
	for (int c = 1, n; cin >> n && n; c++) {
		vector<Info> v(n);
		for (auto& [year, a, b] : v) cin >> year >> a >> b;

		auto Sol = [&]() -> int {
			for (int y = 0; y < 10000; y++) {
				bool flag = 1;
				for (const auto& [year, a, b] : v) {
					if (y < a || (y - a) % (b - a) + a != year)
						flag = 0;
				}
				if (flag) return y;
			}
			return -1;
		};

		auto res = Sol();
		cout << "Case #" << c << ":\n";
		if (res == -1) cout << "Unknown bugs detected." << "\n\n";
		else cout << "The actual year is " << res << ".\n\n";
	}
}