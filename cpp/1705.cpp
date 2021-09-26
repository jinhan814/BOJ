#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int cache[1001];

int DFS(int n) {
	if (n <= 2) return n;
	int& ret = cache[n];
	if (ret != -1) return ret; ret = 1;
	for (int i = n & 1; n - i >= 2; i += 2)
		ret += DFS(n - i >> 1);
	return ret;
}

int main() {
	fastio;
	memset(cache, -1, sizeof cache);
	int N; cin >> N;
	for (int n; N-- && cin >> n; cout << DFS(n) << '\n');
}