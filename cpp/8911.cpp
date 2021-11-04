#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		string s; cin >> s;
		int x = 0, y = 0, d = 0, mn_x = 0, mn_y = 0, mx_x = 0, mx_y = 0;
		auto F = [&]() {
			mn_x = min(mn_x, x), mn_y = min(mn_y, y);
			mx_x = max(mx_x, x), mx_y = max(mx_y, y);
		};
		for (const auto& c : s) {
			if (c == 'L') d = d + 1 & 3;
			else if (c == 'R') d = d + 3 & 3;
			else if (c == 'F') x += "1012"[d] - '1', y += "2101"[d] - '1', F();
			else x += "1012"[d + 2 & 3] - '1', y += "2101"[d + 2 & 3] - '1', F();
		}
		cout << (mx_x - mn_x) * (mx_y - mn_y) << '\n';
	}
}