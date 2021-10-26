#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

constexpr int MOD = 12'345'678'910;

int32_t main() {
	fastio;
	vector<int> S; int n; cin >> n;
	while (n--) {
		int t; cin >> t;
		if (t) {
			if (S.back() == -1) S.pop_back(), S.push_back(1);
			else {
				const int val = S.back() * 2 % MOD;
				S.pop_back(); S.pop_back(); S.push_back(val);
			}
			if (S.size() >= 2 && S[S.size() - 2] != -1) {
				const int val = S.back();
				S.pop_back(); (S.back() += val) %= MOD;
			}
		}
		else S.push_back(-1);
	}
	cout << S[0] << '\n';
}