#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Converter {
	int conv[128];
	Converter() { conv['.'] = 0, conv['O'] = 1, conv['X'] = 2; }
	string operator() (int n) {
		string ret;
		for (int i = 0; i < 9; i++, n /= 3) {
			ret.push_back(".OX"[n % 3]);
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}
	int operator() (const string& s) {
		int ret = 0;
		for (int i = 0; i < 9; i++) {
			ret = ret * 3 + conv[s[i]];
		}
		return ret;
	}
} Conv;

bool Check(string s) {
	if (s.find('.') == string::npos) return 1;
	for (int i = 0; i < 3; i++) {
		bool flag = s[i * 3] != '.';
		for (int j = 1; j < 3; j++)
			if (s[i * 3] != s[i * 3 + j]) flag = 0;
		if (flag) return 1;
	}
	for (int i = 0; i < 3; i++) {
		bool flag = s[i] != '.';
		for (int j = 1; j < 3; j++)
			if (s[i] != s[j * 3 + i]) flag = 0;
		if (flag) return 1;
	}
	if (s[0] != '.' && s[0] == s[4] && s[4] == s[8]) return 1;
	if (s[2] != '.' && s[2] == s[4] && s[4] == s[6]) return 1;
	return 0;
}

bitset<27 * 27 * 27> visited;

void Init() {
	queue<int> Q;
	Q.push(0), visited[0] = 1;
	while (Q.size()) {
		auto cur = Conv(Q.front()); Q.pop();
		if (Check(cur)) continue;
		int cnt = 0;
		for (int i = 0; i < 9; i++) if (cur[i] != '.') cnt++;
		for (int i = 0; i < 9; i++) if (cur[i] == '.') {
			auto nxt = cur; nxt[i] = cnt & 1 ? 'O' : 'X';
			if (!visited[Conv(nxt)]) Q.push(Conv(nxt)), visited[Conv(nxt)] = 1;
		}
	}
}

int main() {
	fastio; Init();
	for (string s; cin >> s && s != "end";)
		cout << (visited[Conv(s)] && Check(s) ? "valid" : "invalid") << '\n';
}