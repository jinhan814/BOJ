#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, m, flag = 1; cin >> n >> m;
		vector<int> v(m + 1), prv(n + 1), nxt(m + 1), ans;
		vector<bool> check(n + 1);
		priority_queue<int, vector<int>, greater<>> PQ;

		for (int i = 1; i <= m; i++) {
			cin >> v[i];
			if (v[i]) {
				if (prv[v[i]]) nxt[prv[v[i]]] = i;
				else PQ.push(i);
				prv[v[i]] = i;
			}
		}

		for (int i = 1; i <= m; i++) {
			if (v[i]) {
				if (check[v[i]]) {
					check[v[i]] = 0;
					if (nxt[i]) PQ.push(nxt[i]);
				}
				else { flag = 0; break; }
			}
			else {
				if (PQ.size()) {
					auto val = v[PQ.top()]; PQ.pop();
					check[val] = 1, ans.push_back(val);
				}
				else ans.push_back(0);
			}
		}

		if (flag) {
			cout << "YES" << '\n';
			for (auto& i : ans) cout << i << ' ';
			cout << '\n';
		}
		else cout << "NO" << '\n';
	}
}