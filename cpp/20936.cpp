#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

template<typename T = int, typename F = less<T>>
struct Priority_queue {
	Priority_queue(const F& f = F{}) : insert(f), erase(f) {}
	T top() { __Erase(); return insert.top(); }
	void push(T val) { __Erase(); insert.push(val); }
	void pop(T val) { __Erase(); erase.push(val); }
	size_t size() { __Erase(); return insert.size(); }
	bool empty() { __Erase(); return insert.empty(); }
private:
	priority_queue<T, vector<T>, F> insert, erase;
	void __Erase() {
		while (erase.size() && insert.top() == erase.top())
			insert.pop(), erase.pop();
	}
};

struct UnionFind {
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
		if (a == b) return;
		if (a > b) swap(a, b);
		par[a] += par[b], par[b] = a;
    }
	int L(int x) { return Find(x); }
	int R(int x) { return x = Find(x), x + -par[x] - 1; }
};

struct Info {
	char cmd; int idx; ll val;
	static int pr(char c) { return c == '*' || c == '/'; }
	bool operator< (const Info& i) const {
		if (val != i.val) return val < i.val;
		if (pr(cmd) != pr(i.cmd)) return pr(cmd) < pr(i.cmd);
		return idx > i.idx;
	}
	bool operator== (const Info& i) const = default;
};

constexpr ll Eval(const char& cmd, const ll& a, const ll& b) {
	if (cmd == '+') return a + b;
	if (cmd == '-') return a - b;
	if (cmd == '*') return a * b;
	if (cmd == '/') return a / b;
}

vector<string> Tokenize(const string& s) {
	vector<string> ret;
	for (int i = 0; i < s.size();) {
		if (isdigit(s[i])) {
			string t;
			while (i < s.size() && isdigit(s[i])) t.push_back(s[i++]);
			while (t.size() > 1 && t[0] == '0') t.erase(t.begin());
			ret.push_back(t);
		}
		else ret.push_back(string(1, s[i++]));
	}
	return ret;
}

ll Sol(const string& s) {
	const auto v = Tokenize(s);
	const int n = v.size() + 1 >> 1;
	vector<ll> val(n); string cmd;
	for (int i = 0; i < n; i++) val[i] = stoll(v[2 * i]);
	for (int i = 1; i < n; i++) cmd.push_back(v[2 * i - 1][0]);
	UnionFind UF(n); Priority_queue<Info> PQ;
	auto F = [&](int i) -> Info {
		const auto l = val[UF.Find(i - 1)], r = val[UF.Find(i)];
		return { cmd[i - 1], i, Eval(cmd[i - 1], l, r) };
	};
	for (int i = 1; i < n; i++) PQ.push(F(i));
	while (PQ.size()) {
		auto [cmd, i, cur] = PQ.top(); PQ.pop(PQ.top());
		if (UF.L(i - 1)) PQ.pop(F(UF.L(i - 1)));
		if (UF.R(i) + 1 < n) PQ.pop(F(UF.R(i) + 1));
		UF.Union(i - 1, i);
		val[UF.Find(i)] = cur;
		if (UF.L(i - 1)) PQ.push(F(UF.L(i - 1)));
		if (UF.R(i) + 1 < n) PQ.push(F(UF.R(i) + 1));
	}
	return val[0];
}

int main() {
	fastio;
	string s; cin >> s;
	cout << Sol(s) << '\n';
}