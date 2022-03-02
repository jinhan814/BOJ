#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

string Conv(const string& s) {
	string ret;
	for (auto& c : s) {
		int val = c < 'A' ? c - '0' : c - 'A' + 10;
		for (int i = 3; ~i; i--) ret.push_back(!!(val & 1 << i) | 48);
	}
	return ret;
}

char Hex(int n) { return n < 10 ? n + '0' : n - 10 + 'A'; }

char Alpha(int n) { return "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:"[n]; }

int F(const string& s, int l, int r) { // [l, r)
	int ret = 0;
	for (int i = l; i < r; i++) ret = ret << 1 | s[i] & 1;
	return ret;
}

pair<int, string> Sol(string s) {
	string ret; int cnt = 0;
	s = Conv(s);
	for (int i = 0;;) {
		if (s[i + 3] & 1) { // Numeric
			int t = F(s, i + 4, i + 14);
			cnt += t, i += 14;
			for (; t > 0; t -= 3) {
				int sz = t > 2 ? 10 : t > 1 ? 7 : 4;
				int res = F(s, i, i + sz);
				if (t >= 3) ret.push_back(res / 100 + '0');
				if (t >= 2) ret.push_back(res / 10 % 10 + '0');
				ret.push_back(res % 10 + '0');
				i += sz;
			}
		}
		else if (s[i + 2] & 1) { // Alphanumeric
			int t = F(s, i + 4, i + 13);
			cnt += t, i += 13;
			for (; t > 0; t -= 2) {
				int sz = t > 1 ? 11 : 6;
				int res = F(s, i, i + sz);
				if (t > 1) {
					ret.push_back(Alpha(res / 45));
					if (ret.back() == '#') ret.pop_back(), ret += "\\#";
				}
				ret.push_back(Alpha(res % 45));
				if (ret.back() == '#') ret.pop_back(), ret += "\\#";
				i += sz;
			}
		}
		else if (s[i + 1] & 1) { // 8 bit byte
			int t = F(s, i + 4, i + 12);
			cnt += t, i += 12;
			for (; t--; i += 8) {
				if (int res = F(s, i, i + 8); 0x20 <= res && res <= 0x7e) {
					ret.push_back(res);
					if (ret.back() == '#') ret.pop_back(), ret += "\\#";
				}
				else {
					ret.push_back('\\');
					ret.push_back(Hex(F(s, i, i + 4)));
					ret.push_back(Hex(F(s, i + 4, i + 8)));
				}
			}
		}
		else if (s[i] & 1) { // Kanji
			int t = F(s, i + 4, i + 12);
			cnt += t, i += 12;
			for (; t--; i += 13) {
				if (int res = F(s, i, i + 13); 0x20 <= res && res <= 0x7e) {
					ret.push_back(res);
					if (ret.back() == '#') ret.pop_back(), ret += "\\#";
				}
				else {
					ret.push_back('#');
					ret.push_back(s[i]);
					ret.push_back(Hex(F(s, i + 1, i + 5)));
					ret.push_back(Hex(F(s, i + 5, i + 9)));
					ret.push_back(Hex(F(s, i + 9, i + 13)));
				}
			}
		}
		else break;
	}
	return { cnt, ret };
}

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		string s; cin >> s;
		auto [n, res] = Sol(s);
		cout << n << ' ' << res << '\n';
	}
}