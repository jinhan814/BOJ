#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

string a, b, ans;

// a[l1, r1), b[l2, r2)
void Sol(int l1, int r1, int l2, int r2) { // DP[l1][r1] -> DP[l2][r2]
	if (r1 < l1 || r2 < l2) return;
	if (l1 == r1) { ans += string(r2 - l2, 'a'); return; }
	if (l2 == r2) { ans += string(r1 - l1, 'd'); return; }

	// 1. Calc DP
	const int n = r1 - l1, m = r2 - l2, mid = n >> 1;
	vector<int> DP1(m + 1), DP2(m + 1), prv;
	for (int i = 0; i <= m; i++) DP1[i] = i, DP2[i] = m - i;
	for (int i = 1; i <= mid; i++) {
		prv = DP1;
		for (int j = 0; j <= m; j++) {
			int mn = 1e9, flag = i && j && a[l1 + i - 1] == b[l2 + j - 1];
			if (i) mn = min(mn, prv[j] + 1);
			if (j) mn = min(mn, DP1[j - 1] + 1);
			if (i && j) mn = min(mn, prv[j - 1] + !flag);
			DP1[j] = mn;
		}
	}
	for (int i = n - 1; i > mid; i--) {
		prv = DP2;
		for (int j = m; j >= 0; j--) {
			int mn = 1e9, flag = a[l1 + i] == b[l2 + j];
			if (i < n) mn = min(mn, prv[j] + 1);
			if (j < m) mn = min(mn, DP2[j + 1] + 1);
			if (i < n && j < m) mn = min(mn, prv[j + 1] + !flag);
			DP2[j] = mn;
		}
	}

	// 2. Find Opt
	int mn = 1e9, opt1 = -1, opt2 = -1;
	for (int j = 0; j <= m; j++) {
		if (mn > DP1[j] + DP2[j] + 1)
			mn = DP1[j] + DP2[j] + 1, opt1 = opt2 = j;
		if (j < m) {
			bool flag = a[l1 + mid] == b[l2 + j];
			if (mn > DP1[j] + DP2[j + 1] + !flag)
				mn = DP1[j] + DP2[j + 1] + !flag, opt1 = j, opt2 = j + 1;
		}
	}

	// 3. DnC
	Sol(l1, l1 + mid, l2, l2 + opt1);
	ans.push_back(opt1 ^ opt2 ? a[l1 + mid] ^ b[l2 + opt1] ? 'm' : 'c' : 'd');
	Sol(l1 + mid + 1, r1, l2 + opt2, r2);
}

void Print() {
	int i = 0, j = 0;
	for (const auto& c : ans) {
		if (c == 'a') cout << c << ' ' << b[j++] << '\n';
		else if (c == 'd') cout << c << ' ' << a[i++] << '\n';
		else cout << c << ' ' << b[j++] << '\n', i++;
	}
}

int main() {
	fastio;
	cin >> a >> b;
	Sol(0, a.size(), 0, b.size());
	Print();
}