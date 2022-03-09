#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int SZ = 1'031'926'801;
constexpr int lim1 = (SZ - 2) / 2;
constexpr int lim2 = (SZ - 2) / 3;

bitset<SZ> B;
vector<int> v;

void DFS(int x) {
	B[x] = 1;
	if (x <= lim1 && !B[2 * x + 1]) DFS(2 * x + 1);
	if (x <= lim2 && !B[3 * x + 1]) DFS(3 * x + 1);
}

int main() {
	fastio;
	DFS(1); v.reserve(10'000'000);
	for (int i = 0; v.size() < 10'000'000; i++) {
		if (B[i]) v.push_back(i);
	}
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		cout << v[n - 1] << '\n';
	}
}