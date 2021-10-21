#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, mx, v[1500];
queue<int> Q; stack<int> S;

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < m; i++) Q.push(i);
	while (n--) {
		string s; cin >> s;
		for (int i = Q.size(), t = 0; i --> 0;) {
			auto cur = Q.front(); Q.pop();
			if (s[cur] == '1') mx = max(mx, ++v[cur] * ++t), Q.push(cur);
			else v[cur] = 0, S.push(cur);
		}
		while (S.size()) Q.push(S.top()), S.pop();
	}
	cout << mx << '\n';
}