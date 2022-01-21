#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		vector<int> v(n), I(n);
		for (int i = 0; i < n; i++) cin >> v[i], I[i] = v[i];
		sort(I.begin(), I.end());
		for (auto& i : v) i = lower_bound(I.begin(), I.end(), i) - I.begin();

		vector<int> l(n), r(n), prv(n, -1);
		for (int i = 0; i < n; i++) l[i] = prv[v[i]], prv[v[i]] = i;
		memset(&prv[0], -1, n << 2);
		for (int i = n - 1; i >= 0; i--) r[i] = prv[v[i]], prv[v[i]] = i;

		auto Sol = [&](int st, int en, auto&& Sol) -> bool {
			if (en <= st) return 1;
			for (int i = 0; st + i <= en - i; i++) {
				if ((!~l[st + i] || l[st + i] < st) && (!~r[st + i] || en < r[st + i]))
					return Sol(st, st + i - 1, Sol) && Sol(st + i + 1, en, Sol);
				if ((!~l[en - i] || l[en - i] < st) && (!~r[en - i] || en < r[en - i]))
					return Sol(st, en - i - 1, Sol) && Sol(en - i + 1, en, Sol);
			}
			return 0;
		};
		cout << (Sol(0, n - 1, Sol) ? "non-boring" : "boring") << '\n';
	}
}