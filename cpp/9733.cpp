#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

string DB[] = { "Re", "Pt", "Cc", "Ea", "Tb", "Cm", "Ex" };

int main() {
	fastio;
	map<string, int> M;
	for (int i = 0; i < 7; i++) M[DB[i]] = i;

	vector<int> cnt(7); int sum = 0;
	for (string s; cin >> s; M.count(s) && cnt[M[s]]++) sum++;

	cout << fixed << setprecision(2);
	for (int i = 0; i < 7; i++) cout << DB[i] << ' ' << cnt[i] << ' ' << 1. * cnt[i] / sum << '\n';
	cout << "Total " << sum << " 1.00" << '\n';
}