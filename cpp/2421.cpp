#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, cache[1000][1000];

bool IsPrime(int t1, int t2) {
	const int cur = stoi(to_string(t1) + to_string(t2));
	for (int i = 2; i * i <= cur; i++)
		if (cur % i == 0) return 0;
	return 1;
}

int DFS(int t1, int t2) {
	if (t1 == 1 && t2 == 1) return 0;
	int& ret = cache[t1][t2];
	if (ret != -1) return ret; ret = 0;
	if (t1 > 1) ret = max(ret, DFS(t1 - 1, t2));
	if (t2 > 1) ret = max(ret, DFS(t1, t2 - 1));
	return ret += IsPrime(t1, t2);
}

int main() {
	fastio;
	cin >> n; memset(cache, -1, sizeof cache);
	cout << DFS(n, n) << '\n';
}