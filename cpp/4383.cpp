#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bitset<3000> check;

int main() {
	fastio;
	for (int n; cin >> n;) {
		vector<int> v(n); check.reset();
		for (int i = 0; i < n; i++) cin >> v[i];

		auto Sol = [&]() -> bool {
			for (int i = 1; i < n; i++) {
				int diff = abs(v[i] - v[i - 1]);
				if (diff < 1 || diff >= n || check[diff]) return 0;
				check[diff] = 1;
			}
			return 1;
		};
		cout << (Sol() ? "Jolly" : "Not jolly") << '\n';
	}
}