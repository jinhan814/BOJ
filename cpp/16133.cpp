#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;
using It = vector<string>::iterator;

ll Pow(ll x, ll n) {
	ll ret = 1;
	for (; n; n >>= 1) { if (n & 1) ret *= x; x *= x; }
	return ret;
}

ll Sqrt(ll x) {
	if (x <= 0) return 0;
	ll lo = 1, hi = x + 1;
	while (lo + 1 < hi) {
		ll mid = lo + hi >> 1;
		if (x / mid >= mid) lo = mid;
		else hi = mid;
	}
	return lo;
}

vector<string> Tokenize(const string& s) {
	vector<string> ret;
	for (int i = 0; i < s.size(); i++) {
		if (isdigit(s[i])) {
			string t;
			while (i < s.size() && isdigit(s[i])) t.push_back(s[i++]); --i;
			ret.push_back(t);
		}
		else ret.push_back(string(1, s[i]));
	}
	ret.pop_back();
	return ret;
}

ll ParseExpr(It& st, const It& en);
ll ParseTerm(It& st, const It& en);
ll ParseFactor(It& st, const It& en);
ll ParsePower(It& st, const It& en);
ll ParseRoot(It& st, const It& en);

ll ParseExpr(It& st, const It& en) {
	auto ret = ParseTerm(st, en);
	while (st != en && (*st == "+" || *st == "-")) {
		auto cmd = *st++;
		auto res = ParseTerm(st, en);
		if (cmd == "+") ret += res;
		else ret -= res;
	}
	return ret;
}

ll ParseTerm(It& st, const It& en) {
	auto ret = ParseFactor(st, en);
	while (st != en && (*st == "*" || *st == "/")) {
		auto cmd = *st++;
		auto res = ParseFactor(st, en);
		if (cmd == "*") ret *= res;
		else ret /= res;
	}
	return ret;
}

ll ParseFactor(It& st, const It& en) {
	auto ret = ParsePower(st, en);
	if (st != en && *st == "^") {
		auto res = ParseFactor(++st, en);
		return Pow(ret, res);
	}
	else {
		return ret;
	}
}

ll ParsePower(It& st, const It& en) {
	if (*st == "#") {
		auto res = ParsePower(++st, en);
		return Sqrt(res);
	}
	else {
		return ParseRoot(st, en);
	}
}

ll ParseRoot(It& st, const It& en) {
	if (*st == "(") {
		auto res = ParseExpr(++st, en); ++st;
		return res;
	}
	else {
		return stoll(*st++);
	}
}

int main() {
	fastio;
	string s; cin >> s;
	auto v = Tokenize(s);
	auto st = v.begin(), en = v.end();
	cout << ParseExpr(st, en) << '\n';
}