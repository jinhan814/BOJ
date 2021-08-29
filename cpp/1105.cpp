#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string a, b; cin >> a >> b;

	auto Sol = [&]() -> int {
		if (a.size() != b.size()) return 0;
		int ret = 0;
		for (int i = 0; i < a.size() && a[i] == b[i]; i++)
			if (a[i] == '8') ret++;
		return ret;
	};

	cout << Sol() << '\n';
}