#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bool Sol0(vector<int> v) { // already finished
	for (int i = 0; i < v.size(); i++) if (v[i] != i) return 0;
	cout << 1 << ' ' << 1 << '\n';
	cout << 1 << ' ' << 1 << '\n';
	return 1;
}

bool Sol1(vector<int> v) { // distinct interval
	vector<pair<int, int>> t;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == i) continue;
		const int nxt = v[i]; t.push_back({ i, nxt });
		if (i >= nxt) return 0;
		reverse(v.begin() + i, v.begin() + nxt + 1); i = nxt;
	}
	if (t.size() > 2) return 0;
	for (int i = 0; i < v.size(); i++) if (v[i] != i) return 0;
	if (t.size() == 1) {
		cout << t[0].first + 1 << ' ' << t[0].second + 1 << '\n';
		cout << 1 << ' ' << 1 << '\n';
	}
	else {
		cout << t[0].first + 1 << ' ' << t[0].second + 1 << '\n';
		cout << t[1].first + 1 << ' ' << t[1].second + 1 << '\n';
	}
	return 1;
}

bool Sol2(vector<int> v) { // overlapping interval
	int t1 = -1, t2 = -1;
	for (int i = 0; i < v.size() && t1 == -1; i++) if (v[i] != i) t1 = i;
	for (int i = v.size(); i --> 0 && t2 == -1;) if (v[i] != i) t2 = i;
	for (auto& [a, b, c, d] : vector<tuple<int, int, int, int>>{
		{ t1, v[t2] + t2 - v[t1], v[t2], t2 },
		{ t1 + v[t1] - v[t2], t2, t1, v[t1] },
		{ t1, t2, t1, v[t2] },
		{ t1 + t2 - v[t2], t2, t1, t2 },
		{ t1, t1 + t2 - v[t1], t1, t2 },
		{ t1, t2, v[t1], t2 }
	}) {
		if (a > b || c > d) continue;
		if (a < 0 || a >= v.size()) continue;
		if (b < 0 || b >= v.size()) continue;
		if (c < 0 || c >= v.size()) continue;
		if (d < 0 || d >= v.size()) continue;
		auto w = v; bool flag = 1;
		reverse(w.begin() + a, w.begin() + b + 1);
		reverse(w.begin() + c, w.begin() + d + 1);
		for (int i = 0; i < w.size(); i++) if (w[i] != i) flag = 0;
		if (!flag) continue;
		cout << a + 1 << ' ' << b + 1 << '\n';
		cout << c + 1 << ' ' << d + 1 << '\n';
		return 1;
	}
	cout << t1 + 1 << ' ' << t2 + 1 << '\n';
	reverse(v.begin() + t1, v.begin() + t2 + 1);
	t1 = -1, t2 = -1;
	for (int i = 0; i < v.size() && t1 == -1; i++) if (v[i] != i) t1 = i;
	for (int i = v.size(); i --> 0 && t2 == -1;) if (v[i] != i) t2 = i;
	cout << t1 + 1 << ' ' << t2 + 1 << '\n';
	return 1;
}

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i], v[i]--;
	Sol0(v) || Sol1(v) || Sol2(v);
}