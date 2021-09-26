#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int v[2][9];
	for (int i = 0; i < 2; i++) for (int j = 0; j < 9; j++) cin >> v[i][j];

	auto flag_1 = [&]() -> bool {
		for (int j = 0, t = 0; j < 9; j++) {
			for (int i = 0; i < 2; i++) {
				t += i ? -v[i][j] : v[i][j];
				if (t > 0) return 1;
			}
		}
		return 0;
	};

	auto flag_2 = [&]() -> bool {
		return reduce(v[0], v[0] + 9) < reduce(v[1], v[1] + 9);
	};

	cout << (flag_1() && flag_2() ? "Yes" : "No") << '\n';
}