#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using u16 = uint16_t;
using It = vector<string>::iterator;

struct Matrix : public vector<vector<u16>> {
	Matrix() : vector<vector<u16>>() {}
	Matrix(u16 val) : vector<vector<u16>>(1, vector<u16>(1, val)) {}
	Matrix(int n, int m) : vector<vector<u16>>(n, vector<u16>(m)) {}
	friend Matrix operator+ (const Matrix& a, const Matrix& b) { // a+b
		Matrix ret(a.size(), a[0].size());
		for (int i = 0; i < a.size(); i++) for (int j = 0; j < a[0].size(); j++) ret[i][j] = a[i][j] + b[i][j];
		return ret;
	}
	friend Matrix operator- (const Matrix& a, const Matrix& b) { // a-b
		Matrix ret(a.size(), a[0].size());
		for (int i = 0; i < a.size(); i++) for (int j = 0; j < a[0].size(); j++) ret[i][j] = a[i][j] - b[i][j];
		return ret;
	}
	friend Matrix operator* (const Matrix& a, const Matrix& b) { // a*b
		if (a[0].size() == b.size()) {
			Matrix ret(a.size(), b[0].size());
			for (int i = 0; i < a.size(); i++) for (int j = 0; j < b[0].size(); j++)
				for (int k = 0; k < a[0].size(); k++) ret[i][j] += a[i][k] * b[k][j];
			return ret;
		}
		else {
			auto& t = a.size() == 1 && a[0].size() == 1 ? a : b;
			auto ret = a.size() == 1 && a[0].size() == 1 ? b : a;
			for (int i = 0; i < ret.size(); i++) for (int j = 0; j < ret[0].size(); j++) ret[i][j] *= t[0][0];
			return ret;
		}
	}
	Matrix operator- () const { // -c
		const int n = this->size(), m = (*this)[0].size();
		Matrix ret(n, m);
		return ret - *this;
	}
	Matrix operator~ () const { // c'
		const int n = this->size(), m = (*this)[0].size();
		Matrix ret(m, n);
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) ret[j][i] = (*this)[i][j];
		return ret;
	}
	Matrix operator| (const Matrix& b) const { // [a b]
		const auto& a = *this;
		Matrix ret(a.size(), a[0].size() + b[0].size());
		for (int i = 0; i < a.size(); i++) for (int j = 0; j < a[0].size(); j++) ret[i][j] = a[i][j];
		for (int i = 0; i < b.size(); i++) for (int j = 0; j < b[0].size(); j++) ret[i][a[0].size() + j] = b[i][j];
		return ret;
	}
	Matrix operator|| (const Matrix& b) const { // [a;b]
		const auto& a = *this;
		Matrix ret(a.size() + b.size(), a[0].size());
		for (int i = 0; i < a.size(); i++) for (int j = 0; j < a[0].size(); j++) ret[i][j] = a[i][j];
		for (int i = 0; i < b.size(); i++) for (int j = 0; j < b[0].size(); j++) ret[a.size() + i][j] = b[i][j];
		return ret;
	}
	Matrix operator() (const Matrix& a, const Matrix& b) const { // c(a,b)
		Matrix ret(a[0].size(), b[0].size());
		for (int i = 0; i < a[0].size(); i++) for (int j = 0; j < b[0].size(); j++) ret[i][j] = (*this)[a[0][i] - 1][b[0][j] - 1];
		return ret;
	}
	void Print() const {
		for (auto& i : *this) {
			for (auto& j : i) cout << (j < 32768 ? j : j - 32768) << ' ';
			cout << '\n';
		}
	}
};

template<typename It>
vector<string> Tokenize(It st, const It& en) {
	vector<string> ret;
	while (st != en) {
		if (isdigit(*st)) {
			ret.push_back(string(1, *st++));
			while (st != en && isdigit(*st)) ret.back().push_back(*st++);
		}
		else ret.push_back(string(1, *st++));
	}
	return ret;
}

Matrix val[26];

Matrix ParseExpr(It& st, const It& en);
Matrix ParseTerm(It& st, const It& en);
Matrix ParseFactor(It& st, const It& en);
Matrix ParsePrimary(It& st, const It& en);
Matrix ParseRowSeq(It& st, const It& en);
Matrix ParseRow(It& st, const It& en);

Matrix ParseExpr(It& st, const It& en) {
	auto ret = ParseTerm(st, en);
	while (st != en && (*st == "+" || *st == "-")) {
		auto cmd = *st++;
		auto res = ParseTerm(st, en);
		if (cmd == "+") ret = ret + res;
		else ret = ret - res;
	}
	return ret;
}

Matrix ParseTerm(It& st, const It& en) {
	auto ret = ParseFactor(st, en);
	while (st != en && *st == "*") {
		auto res = ParseFactor(++st, en);
		ret = ret * res;
	}
	return ret;
}

Matrix ParseFactor(It& st, const It& en) {
	if (*st == "-") {
		auto res = ParseFactor(++st, en);
		return -res;
	}
	return ParsePrimary(st, en);
}

Matrix ParsePrimary(It& st, const It& en) {
	auto ret = [&]() -> Matrix {
		if (isdigit((*st)[0])) { auto ret = Matrix(stoi(*st++)); return ret; }
		else if (isalpha((*st)[0])) { auto ret = val[(*st++)[0] - 'A']; return ret; }
		else if (*st == "(") { auto ret = ParseExpr(++st, en); ++st; return ret; }
		else if (*st == "[") { auto ret = ParseRowSeq(++st, en); ++st; return ret; }
	}();
	while (st != en && (*st == "'" || *st == "(")) {
		if (*st == "'") ++st, ret = ~ret;
		else {
			auto res1 = ParseExpr(++st, en);
			auto res2 = ParseExpr(++st, en); ++st;
			ret = ret(res1, res2);
		}
	}
	return ret;
}

Matrix ParseRowSeq(It& st, const It& en) {
	auto ret = ParseRow(st, en);
	while (st != en && *st == ";") {
		auto res = ParseRow(++st, en);
		ret = ret || res;
	}
	return ret;
}

Matrix ParseRow(It& st, const It& en) {
	auto ret = ParseExpr(st, en);
	while (st != en && *st == " ") {
		auto res = ParseExpr(++st, en);
		ret = ret | res;
	}
	return ret;
}

int main() {
	fastio;
	for (int n; cin >> n && n;) {
		cin.ignore();
		while (n--) {
			string s; getline(cin, s);
			auto v = Tokenize(s.begin() + 2, s.end() - 1);
			auto st = v.begin(), en = v.end();
			val[s[0] - 'A'] = ParseExpr(st, en);
			val[s[0] - 'A'].Print();
		}
		cout << "-----" << '\n';
	}
}