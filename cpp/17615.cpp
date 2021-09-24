#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	string s; cin >> s;

	auto Sol = [&](const int& n, const string& s) -> int {
		int cnt = 0;
		for (int i = n; i-- > 0 && s[i] == s.back(); cnt++);
		const int cnt_R = count(s.begin(), s.end(), 'R');
		const int cnt_B = n - cnt_R;
		const int t1 = s.back() == 'R' ? cnt_R - cnt : cnt_R;
		const int t2 = s.back() == 'B' ? cnt_B - cnt : cnt_B;
		return min(t1, t2);
	};

	int ans = Sol(n, s);
	reverse(s.begin(), s.end());
	ans = min(ans, Sol(n, s));
	cout << ans << '\n';
}