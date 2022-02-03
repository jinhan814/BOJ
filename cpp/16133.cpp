#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

/* =================================================================== */

using i64 = int64_t;

struct Node { virtual i64 eval() { return 0; } };

struct IntLiteral : public Node {
	string s;
	IntLiteral(string s) : s(s) {}
	virtual i64 eval() { return stoll(s); }
};

struct Add : public Node {
	shared_ptr<Node> l, r;
	Add(shared_ptr<Node> l, shared_ptr<Node> r) : l(l), r(r) {}
	virtual i64 eval() { return l->eval() + r->eval(); }
};

struct Sub : public Node {
	shared_ptr<Node> l, r;
	Sub(shared_ptr<Node> l, shared_ptr<Node> r) : l(l), r(r) {}
	virtual i64 eval() { return l->eval() - r->eval(); }
};

struct Mul : public Node {
	shared_ptr<Node> l, r;
	Mul(shared_ptr<Node> l, shared_ptr<Node> r) : l(l), r(r) {}
	virtual i64 eval() { return l->eval() * r->eval(); }
};

struct Div : public Node {
	shared_ptr<Node> l, r;
	Div(shared_ptr<Node> l, shared_ptr<Node> r) : l(l), r(r) {}
	virtual i64 eval() { return l->eval() / r->eval(); }
};

struct Pow : public Node {
	shared_ptr<Node> l, r;
	Pow(shared_ptr<Node> l, shared_ptr<Node> r) : l(l), r(r) {}
	static i64 _Pow(i64 x, i64 n) {
		i64 ret = 1;
		for (; n; n >>= 1) { if (n & 1) ret *= x; x *= x; }
		return ret;
	}
	virtual i64 eval() { return _Pow(l->eval(), r->eval()); }
};

struct Sqrt : public Node {
	shared_ptr<Node> p;
	Sqrt(shared_ptr<Node> p) : p(p) {}
	static i64 _Sqrt(i64 x) { // x = mid * q + r >= mid * q >= mid * mid
		if (x <= 0) return 0;
		i64 lo = 1, hi = x + 1;
		while (lo + 1 < hi) {
			i64 mid = lo + hi >> 1;
			if (x / mid >= mid) lo = mid;
			else hi = mid;
		}
		return lo;
	}
	virtual i64 eval() { return _Sqrt(p->eval()); }
};

/* =================================================================== */

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

/* =================================================================== */

using It    = vector<string>::iterator;
using pNode = shared_ptr<Node>;

pNode ParseExpr(It& st, const It& en);
pNode ParseTerm(It& st, const It& en);
pNode ParseFactor(It& st, const It& en);
pNode ParsePower(It& st, const It& en);
pNode ParseRoot(It& st, const It& en);

pNode ParseExpr(It& st, const It& en) {
	auto ret = ParseTerm(st, en);
	while (st != en && (*st == "+" || *st == "-")) {
		auto cmd = *st++;
		auto res = ParseTerm(st, en);
		if (cmd == "+") ret = make_shared<Add>(ret, res);
		else ret = make_shared<Sub>(ret, res);
	}
	return ret;
}

pNode ParseTerm(It& st, const It& en) {
	auto ret = ParseFactor(st, en);
	while (st != en && (*st == "*" || *st == "/")) {
		auto cmd = *st++;
		auto res = ParseFactor(st, en);
		if (cmd == "*") ret = make_shared<Mul>(ret, res);
		else ret = make_shared<Div>(ret, res);
	}
	return ret;
}

pNode ParseFactor(It& st, const It& en) {
	auto ret = ParsePower(st, en);
	if (st != en && *st == "^") {
		auto res = ParseFactor(++st, en);
		return make_shared<Pow>(ret, res);
	}
	else {
		return ret;
	}
}

pNode ParsePower(It& st, const It& en) {
	if (*st == "#") {
		auto res = ParsePower(++st, en);
		return make_shared<Sqrt>(res);
	}
	else {
		return ParseRoot(st, en);
	}
}

pNode ParseRoot(It& st, const It& en) {
	if (*st == "(") {
		auto res = ParseExpr(++st, en); ++st;
		return res;
	}
	else {
		return make_shared<IntLiteral>(*st++);
	}
}

/* =================================================================== */

int main() {
	fastio;
	string s; cin >> s;
	auto v = Tokenize(s);
	auto st = v.begin(), en = v.end();
	auto res = ParseExpr(st, en);
	cout << res->eval() << '\n';
}