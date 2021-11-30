#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	for (int c = 1; c <= N; c++) {
		string a, b; cin >> a >> b;

		auto Sol = [&]() -> int {
			int ret = 0;
			for (const char& c : a) {
				int mn = 1e9;
				for (int i = 0; i < 26; i++) if (b.find('a' + i) != -1)
                    if (c < 'a' + i) mn = min(mn, min('a' + i - c, 26 + c - 'a' - i));
                    else mn = min(mn, min(c - 'a' - i, 26 + 'a' + i - c));
				ret += mn;
			}
			return ret;
		};

		cout << "Case #" << c << ": " << Sol() << '\n';
	}
}