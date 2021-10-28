#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct EquationParser {
	tuple<int, int, int> F(string s) {
		int x = 0, y = 0, c = 0;
		stringstream in(s);
		for (int i = 0, flag = 0; in >> s; i++) {
			if (i & 1) flag = s == "-";
			else {
				auto t = s; t.pop_back(); t = t.empty() ? "1" : t == "-" ? "-1" : t;
				if (s.back() == 'x') x += (flag ? -1 : 1) * stoi(t);
				else if (s.back() == 'y') y += (flag ? -1 : 1) * stoi(t);
				else c += (flag ? -1 : 1) * stoi(s);
			}
		}
		return { x, y, c };
	}
	tuple<int, int, int> operator() (string s) {
		auto pos = s.find('=');
		auto [lx, ly, lc] = F(s.substr(0, pos - 1));
		auto [rx, ry, rc] = F(s.substr(pos + 2, s.size()));
		return { lx - rx, ly - ry, rc - lc };
	}
} Parser;

tuple<int, int, int, int> Sol(const string& a, const string& b) {
	auto [ax, ay, ac] = Parser(a);
	auto [bx, by, bc] = Parser(b);
	if (ax == 0 && ay == 0 || bx == 0 && by == 0) { // case 1. 0 = c
		if (bx == 0 && by == 0) swap(ax, bx), swap(ay, by), swap(ac, bc);
		if (ac) return { 0, 0, 0, 0 };
		if (bx && !by) return { bc, bx, 0, 0 };
		if (by && !bx) return { 0, 0, bc, by };
		return { 0, 0, 0, 0 };
	}
	else if (ay == 0 || by == 0) { // case 2. x = c
		if (by == 0) swap(ax, bx), swap(ay, by), swap(ac, bc);
		if (by == 0) {
			if (bx * ac == ax * bc) return { ac, ax, 0, 0 };
			return { 0, 0, 0, 0 };
		}
	}
	else if (ax == 0 || bx == 0) { // case 3. y = c
		if (bx == 0) swap(ax, bx), swap(ay, by), swap(ac, bc);
		if (bx == 0) {
			if (by * ac == ay * bc) return { 0, 0, ac, ay };
			return { 0, 0, 0, 0 };
		}
	}
	// case 4. x + y = c
	if (ax * by == bx * ay) return { 0, 0, 0, 0 };
	return { by * ac - ay * bc, by * ax - ay * bx, bx * ac - ax * bc, bx * ay - ax * by };
}

void Print(int a, int b) {
    if (b) {
        if (!a) cout << 0 << '\n';
        else if (b > 1) cout << a << '/' << b << '\n';
        else cout << a << '\n';
    }
    else cout << "don\'t know" << '\n';
}

int main() {
	fastio;
	int N; cin >> N; cin.ignore();
	for (string a, b, _; N-- && getline(cin, a) && getline(cin, b); getline(cin, _)) {
		auto [x1, x2, y1, y2] = Sol(a, b);
		if (x2 < 0) x1 = -x1, x2 = -x2;
		if (y2 < 0) y1 = -y1, y2 = -y2;
		if (int g = gcd(abs(x1), abs(x2)); g > 1) x1 /= g, x2 /= g;
		if (int g = gcd(abs(y1), abs(y2)); g > 1) y1 /= g, y2 /= g;
		Print(x1, x2), Print(y1, y2); cout << '\n';
	}
}