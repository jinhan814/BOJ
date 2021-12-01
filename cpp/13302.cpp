#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, check[101], DP[100][50];
vector<int> v;

int Sol(int cur, int cnt) {
	if (cur >= v.size()) return 0;
	int& ret = DP[cur][cnt], t1 = cur, t2 = cur;
	if (ret != -1) return ret; ret = Sol(cur + 1, cnt) + 10000;
	if (cnt >= 3) ret = min(ret, Sol(cur + 1, cnt - 3));
	while (t1 < v.size() && v[t1] < v[cur] + 3) t1++; ret = min(ret, Sol(t1, cnt + 1) + 25000);
	while (t2 < v.size() && v[t2] < v[cur] + 5) t2++; ret = min(ret, Sol(t2, cnt + 2) + 37000);
	return ret;
}

int main() {
	fastio;
	memset(DP, -1, sizeof DP);
	cin >> n >> m;
	for (int t; m-- && cin >> t; check[t] = 1);
	for (int i = 1; i <= n; i++) if (!check[i]) v.push_back(i);
	cout << Sol(0, 0) << '\n';
}