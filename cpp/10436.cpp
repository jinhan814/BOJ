#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

pii Sol(int a, int b) {
	if (b == 1) return { 1, a + 1 };
	const int t = (a - 1) / b;
	int p = a - t * b, q = b - p; p += q;
	return { p, q + t * p };
}

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int t, a, b; string s; cin >> t >> s;
		for (auto& i : s) if (i == '/') i = ' ';
		stringstream in(s); in >> a >> b;
		auto res = Sol(a, b);
		cout << t << ' ' << res.first << '/' << res.second << '\n';
	}
}