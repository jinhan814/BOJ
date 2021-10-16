#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int64_t ans = 0;
	for (string s; cin >> s; ans += stoi(s)) s.erase(s.find('.'), 1);
	cout << ans / 100 << '.' << setw(2) << setfill('0') << ans % 100 << '\n';
}