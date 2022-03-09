#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

i64 F[90]{ 0, 1 };

string Sol(const i64 n) {
	if (n == 0) return "";
	if (n == 1) return "1";
	for (i64 i = 0, sum = 0; i < 90; sum += F[i++]) {
		if (sum + F[i] >= n) {
			auto res = Sol(n - sum - 1);
			return "10" + string(i - 2 - res.size(), '0') + res;
		}
	}
}

int main() {
	fastio;
	for (int i = 2; i < 90; i++) F[i] = F[i - 1] + F[i - 2];
	i64 n; cin >> n;
	cout << Sol(n) << '\n';
}