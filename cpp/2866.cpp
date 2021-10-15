#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
string s[1000];

bool Check(int mid) {
	set<string> S;
	for (int i = 0; i < m; i++) {
		string cur;
		for (int j = mid; j < n; j++) cur.push_back(s[j][i]);
		if (S.count(cur)) return 0;
		S.insert(cur);
	}
	return 1;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> s[i];

	int lo = 0, hi = n;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (Check(mid)) lo = mid;
		else hi = mid;
	}
	cout << lo << '\n';
}