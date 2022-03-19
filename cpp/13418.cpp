#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, par[1001];
vector<int> E1, E2;

int Find(int x) {
    return par[x] < 0 ? x : par[x] = Find(par[x]);
}

bool Union(int a, int b) {
	a = Find(a), b = Find(b);
    return a ^ b ? par[b] = a, 1 : 0;
}

int Max() {
	int ret = 0; memset(par, -1, sizeof par);
	for (int i : E2) if (Union(i & 1023, i >> 10)) ret++;
	return ret;
}

int Min() {
	int ret = n; memset(par, -1, sizeof par);
	for (int i : E1) if (Union(i & 1023, i >> 10)) ret--;
	return ret;
}

int main() {
    fastio;
    cin >> n >> m;
	for (int i = 0; i <= m; i++) {
        int a, b, c; cin >> a >> b >> c;
		if (c) E1.push_back(a | b << 10);
		else E2.push_back(a | b << 10);
	}
	auto mx = Max(), mn = Min();
	cout << (mx + mn) * (mx - mn) << '\n';
}