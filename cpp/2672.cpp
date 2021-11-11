#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

struct Event {
	int x1, x2, y, delta;
	bool operator< (const Event& i) { return y < i.y; }
};

int32_t main() {
	fastio;
	int n; cin >> n;
	vector<Event> E;
	for (int i = 0, v[4]; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			string s; cin >> s;
			if (~s.find('.')) s.erase(s.begin() + s.find('.'));
			else s.push_back('0');
			v[j] = stoi(s);
		}
		E.push_back({ v[0], v[0] + v[2], v[1], 1 });
		E.push_back({ v[0], v[0] + v[2], v[1] + v[3], -1 });
	}

	sort(E.begin(), E.end(), [](const Event& a, const Event& b) {
		return a.y ^ b.y ? a.y < b.y : a.delta < b.delta;
	});

	int check[20'001]{}, cnt = 0, ans = 0;
	for (int i = 0, y = 0; i < E.size();) {
		ans += cnt * (E[i].y - y), y = E[i].y;
		for (; i < E.size() && y == E[i].y; i++) {
			if (E[i].delta > 0) {
				for (int x = E[i].x1; x < E[i].x2; x++)
					if (!check[x]++) cnt++;
			}
			else {
				for (int x = E[i].x1; x < E[i].x2; x++)
					if (!--check[x]) cnt--;
			}
		}
	}

	const int t1 = ans / 100, t2 = ans % 100;
	if (t2 < 1) cout << t1 << '\n';
	else if (t2 < 10) cout << t1 << ".0" << t2 << '\n';
	else cout << t1 << '.' << t2 << '\n';
}