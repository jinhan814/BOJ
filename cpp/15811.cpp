t#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string a, b, c; cin >> a >> b >> c;
	vector<int> check(128, -1), visited(10);

	auto Check = [&](int a_dep, int b_dep, int c_dep) -> bool {
		const int sz = min({ a_dep, b_dep, c_dep });
		if (sz == 0) return 1;
		auto t1 = a.substr(a.size() - sz);
		auto t2 = b.substr(b.size() - sz);
		for (auto& i : t1) i = check[i] | 48;
		for (auto& i : t2) i = check[i] | 48;
		const auto s = to_string(stoll(t1) + stoll(t2));
		for (int i = 0; i < sz; i++) if (check[c[c.size() - 1 - i]] != s[s.size() - 1 - i] - '0') return 0;
		return 1;
	};

	auto DFS = [&](int a_dep, int b_dep, int c_dep, auto&& DFS) -> bool {
		if (a_dep == a.size() && b_dep == b.size() && c_dep == c.size()) {
			auto t1 = a, t2 = b, t3 = c;
			for (auto& i : t1) i = check[i] | 48;
			for (auto& i : t2) i = check[i] | 48;
			for (auto& i : t3) i = check[i] | 48;
			return stoll(t1) + stoll(t2) == stoll(t3);
		}
		else {
			if (a_dep < a.size() && check[a[a.size() - 1 - a_dep]] != -1) return DFS(a_dep + 1, b_dep, c_dep, DFS);
			if (b_dep < b.size() && check[b[b.size() - 1 - b_dep]] != -1) return DFS(a_dep, b_dep + 1, c_dep, DFS);
			if (c_dep < c.size() && check[c[c.size() - 1 - c_dep]] != -1) return DFS(a_dep, b_dep, c_dep + 1, DFS);
			if (Check(a_dep, b_dep, c_dep) == 0) return 0;
			if (a_dep < a.size() && (
				a_dep <= b_dep && a_dep <= c_dep ||
				c_dep == c.size() && a_dep <= b_dep ||
				b_dep == b.size() && a_dep <= c_dep ||
				b_dep == b.size() && c_dep == c.size())) {
				for (int i = 0; i < 10; i++) {
					if (visited[i]) continue;
					check[a[a.size() - 1 - a_dep]] = i, visited[i] = 1;
					if (DFS(a_dep + 1, b_dep, c_dep, DFS)) return 1;
					check[a[a.size() - 1 - a_dep]] = -1, visited[i] = 0;
				}
				return 0;
			}
			else if (b_dep < b.size() && (b_dep <= c_dep || c_dep == c.size())) {
				for (int i = 0; i < 10; i++) {
					if (visited[i]) continue;
					check[b[b.size() - 1 - b_dep]] = i, visited[i] = 1;
					if (DFS(a_dep, b_dep + 1, c_dep, DFS)) return 1;
					check[b[b.size() - 1 - b_dep]] = -1, visited[i] = 0;
				}
				return 0;
			}
			else {
				for (int i = 0; i < 10; i++) {
					if (visited[i]) continue;
					check[c[c.size() - 1 - c_dep]] = i, visited[i] = 1;
					if (DFS(a_dep, b_dep, c_dep + 1, DFS)) return 1;
					check[c[c.size() - 1 - c_dep]] = -1, visited[i] = 0;
				}
				return 0;
			}
		}
	};

	cout << (DFS(0, 0, 0, DFS) ? "YES" : "NO") << '\n';
}