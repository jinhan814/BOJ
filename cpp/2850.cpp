#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 1e4 + 7;

int n, m;
string board[10];
map<string, int> cache[10][10];

struct Converter {
private:
	string Type0(const string& s) {
		string ret = s;
		ret.erase(ret.begin()); ret.pop_back();
		ret.push_back('0'), ret.push_back('0');
		return ret;
	}
	string Type1(const string& s) {
		string ret = s;
		ret.erase(ret.begin()); ret.pop_back();
		ret.push_back('0'), ret.push_back(s.back());
		return ret;
	}
	string Type2(const string& s) {
		string ret = s;
		ret.erase(ret.begin()); ret.pop_back();
		for (auto& c : ret) if (c == s.back()) c = s[0];
		ret.push_back('0'), ret.push_back('0');
		return ret;
	}
	string Type3(const string& s) {
		string ret = s;
		ret.erase(ret.begin()); ret.pop_back();
		ret.push_back('0'), ret.push_back(s[0]);
		return ret;
	}
	string Type4(const string& s) {
		string ret = s;
		ret.erase(ret.begin()); ret.pop_back();
		ret.push_back(s[0]), ret.push_back('0');
		return ret;
	}
	string Type5(const string& s) {
		string ret = s;
		ret.erase(ret.begin()); ret.pop_back();
		ret.push_back(s.back()), ret.push_back('0');
		return ret;
	}
	string Type6(const string& s) {
		string ret = s;
		ret.erase(ret.begin()); ret.pop_back();
		ret.push_back('9'), ret.push_back('9');
		return Norm(ret);
	}
public:
	string Norm(const string& s) {
		char check[10]{};
		for (int i = 0, t = 1; i < s.size(); i++) {
			if (s[i] == '0' || check[s[i] & 15]) continue;
			check[s[i] & 15] = t++ | 48;
		}
		string ret(s.size(), '0');
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '0') continue;
			ret[i] = check[s[i] & 15];
		}
		return ret;
	}
	string operator() (int type, const string& cur) {
		switch (type) {
		case 0: return Type0(cur);
		case 1: return Type1(cur);
		case 2: return Type2(cur);
		case 3: return Type3(cur);
		case 4: return Type4(cur);
		case 5: return Type5(cur);
		case 6: return Type6(cur);
		}
	}
} Conv;

bool IsEnd(const string& cur) { // check cur == "00...010"
	for (int i = 0; i < cur.size(); i++) {
		if (i + 2 != cur.size() ^ cur[i] != '1') return 0;
	}
	return 1;
}

int DFS(int x, int y, string cur) {
	cur = Conv.Norm(cur);
	if (x == n) return IsEnd(cur);
	if (cache[x][y].count(cur)) return cache[x][y][cur];

	int& ret = cache[x][y][cur];
	int nx = x, ny = y + 1;
	if (ny >= m) nx++, ny = 0;

	if ((cur[0] > '0' || cur.back() > '0') && board[x][y] == '#' || cur.back() > '0' && y == 0);
	else if (cur[0] > '0' && cur.back() > '0') {
		if (cur[0] == cur.back());
		else ret = DFS(nx, ny, Conv(2, cur));
	}
	else if (cur[0] > '0') {
		ret += DFS(nx, ny, Conv(3, cur));
		ret += DFS(nx, ny, Conv(4, cur));
	}
	else if (cur.back() > '0') {
		ret += DFS(nx, ny, Conv(1, cur));
		ret += DFS(nx, ny, Conv(5, cur));
	}
	else {
		if (board[x][y] != '#') ret += DFS(nx, ny, Conv(6, cur));
		ret += DFS(nx, ny, Conv(0, cur));
	}

	return ret %= MOD;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> board[i];
	string st(m + 1, '0'); st[0] = '1';
	cout << DFS(0, 0, st) << '\n';
}