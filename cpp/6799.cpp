#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using Info = pair<int, string>;

int main() {
	fastio;
	int n; cin >> n;
	Info t1{ 0, "" }, t2{ 0, "" };
	while (n--) {
		string s; int a, b, c; cin >> s >> a >> b >> c;
		Info cur = { -(2 * a + 3 * b + c), s };
		if (t2 > cur) t2 = cur;
		if (t1 > t2) swap(t1, t2);
	}
	if (t1.first) cout << t1.second << '\n';
	if (t2.first) cout << t2.second << '\n';
}