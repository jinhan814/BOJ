#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
vector<int> v[100'001];
bitset<100'001> w;

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int t; cin >> t; v[i].resize(t);
		for (auto& j : v[i]) cin >> j;
	}
	for (int i = 1; i <= n; i++) {
		int t; cin >> t;
		w[i] = t;
	}

	auto GetInit = [&]() -> decltype(w) {
		auto ret = w; ret.flip();
		for (int i = m; i >= 1; i--) {
			bool flag = 0;
			for (auto& j : v[i]) if (ret[j]) flag = 1;
			if (flag) for (auto& j : v[i]) ret[j] = 1;
		}
		ret.flip();
		return ret;
	};
	auto init_state = GetInit();

	auto CheckValid = [&]() -> bool {
		auto state = init_state;
		for (int i = 1; i <= m; i++) {
			bool flag = 0;
			for (auto& j : v[i]) if (state[j]) flag = 1;
			if (flag) for (auto& j : v[i]) state[j] = 1;
		}
		for (int i = 1; i <= n; i++) if (state[i] != w[i]) return 0;
		return 1;
	};

	if (CheckValid()) {
		cout << "YES" << '\n';
		for (int i = 1; i <= n; i++) cout << init_state[i] << ' ';
		cout << '\n';
	}
	else cout << "NO" << '\n';
}