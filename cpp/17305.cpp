#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

i64 Sol(const int m, const vector<i64>& P1, const vector<i64>& P2) {
	i64 ret = 0;
	for (int i = 0; i < P1.size(); i++) {
		if (3 * i > m) break;
		const int j = min<int>((m - 3 * i) / 5, P2.size() - 1);
		ret = max(ret, P1[i] + P2[j]);
	}
	return ret;
}

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<i64> P1(1), P2(1);
	while (n--) {
		int a, b; cin >> a >> b;
		auto& P = a == 3 ? P1 : P2;
		P.push_back(b);
	}
	sort(P1.begin() + 1, P1.end(), greater<>());
	sort(P2.begin() + 1, P2.end(), greater<>());
	for (int i = 1; i < P1.size(); i++) P1[i] += P1[i - 1];
	for (int i = 1; i < P2.size(); i++) P2[i] += P2[i - 1];
	cout << Sol(m, P1, P2) << '\n';
}