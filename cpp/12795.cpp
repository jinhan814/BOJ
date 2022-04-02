#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

struct Line {
	mutable i64 a, b, p;
	bool operator<(const Line& i) const { return a < i.a; }
	bool operator<(i64 x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	static constexpr i64 INF = LLONG_MAX;
	i64 Div(i64 a, i64 b) { return a / b - ((a ^ b) < 0 && a % b != 0); }
	bool Cross(iterator x, iterator y) {
		if (y == end()) return x->p = INF, 0;
		if (x->a == y->a) x->p = x->b > y->b ? INF : -INF;
		else x->p = Div(y->b - x->b, x->a - y->a);
		return x->p >= y->p;
	}
	void Insert(i64 a, i64 b) { // y = ax + b
		auto z = insert({ a, b, 0 }), y = z++, x = y;
		while (Cross(y, z)) z = erase(z);
		if (x != begin() && Cross(--x, y)) Cross(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) Cross(x, erase(y));
	}
	i64 Query(i64 x) {
		auto l = *lower_bound(x);
		return l.a * x + l.b;
	}
} CHT;

int main() {
	fastio;
	int n; cin >> n;
	while (n--) {
		i64 t, a, b; cin >> t >> a;
		if (t & 1) cin >> b, CHT.Insert(a, b);
		else cout << CHT.Query(a) << '\n';
	}
}