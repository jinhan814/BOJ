#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

string p, s;
int n, cache[100][100];

string Norm(const string& s) {
	string ret;
	for (const auto& c : s) {
		if (c != '*') ret.push_back(c);
		else if (ret.empty() || ret.back() != '*') ret.push_back(c);
	}
	return ret;
}

int DFS(int i, int j) {
	if (i == p.size() && j == s.size()) return 1;
	if (i == p.size() - 1 && p[i] == '*') return 1;
	if (i == p.size() || j == s.size()) return 0;
	int& ret = cache[i][j];
	if (ret != -1) return ret; ret = 0;
	if (p[i] == '*') {
		ret |= DFS(i + 1, j);
		ret |= DFS(i, j + 1);
		return ret;
	}
	else {
		if (p[i] != s[j]) return ret = 0;
		return ret = DFS(i + 1, j + 1);
	}
}

int main() {
	fastio;
	cin >> p >> n; p = Norm(p);
	while (n--) {
		cin >> s;
		memset(cache, -1, sizeof cache);
		if (DFS(0, 0)) cout << s << '\n';
	}
}