#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	for (int c = 1; c <= N; c++) {
		int n, m; cin >> n >> m;
		vector<int> v(m);
		for (int i = 0; i < m; i++) cin >> v[i];
		sort(v.begin(), v.end());

		vector<vector<int>> cache(m, vector<int>(m, -1));
		auto DFS = [&](int l, int r, auto&& DFS)-> int {
			if (l > r) return 0;
			int& ret = cache[l][r];
			if (ret != -1) return ret; ret = 1e9;
			const int L = l ? v[l - 1] : 0;
			const int R = r + 1 < m ? v[r + 1] : n + 1;
			for (int i = l; i <= r; i++) {
				ret = min(ret, (R - L - 2) + DFS(l, i - 1, DFS) + DFS(i + 1, r, DFS));
			}
			return ret;
		};

		cout << "Case #" << c << ": ";
		cout << DFS(0, m - 1, DFS) << '\n';
	}
}