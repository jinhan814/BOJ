#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;
using pii = pair<int, int>;

template<int p>
class Lucas {
private:
	int Fac[p], Inv[p];
	static int Pow(int x, int n) {
		int ret = 1;
		for (; n; n >>= 1) {
			if (n & 1) ret = (i64)ret * x % p;
			x = (i64)x * x % p;
		}
		return ret;
	}
public:
	Lucas() {
		Fac[0] = 1;
		for (int i = 1; i < p; i++) Fac[i] = (i64)Fac[i - 1] * i % p;
		Inv[p - 1] = Pow(Fac[p - 1], p - 2);
		for (int i = p - 1; i >= 1; i--) Inv[i - 1] = (i64)Inv[i] * i % p;
	}
	int operator() (int n, int r) {
		int ret = 1;
		while (n || r) {
			const int cn = n % p, cr = r % p;
			if (cn < cr) { ret = 0; break; }
			else ret = ret * ((i64)Fac[cn] * Inv[cr] % p * Inv[cn - cr] % p) % p;
			n /= p, r /= p;
		}
		return ret;
	}
};

pii ExtGCD(int a, int b) {
	if (!b) return { 1, 0 };
	auto res = ExtGCD(b, a % b);
	int x = (res.second % b + b) % b;
	int y = (1 - (long long)a * x) / b;
	return { x, y };
}

pii Sol(int a, int b, int c) {
	int g = gcd(a, b), k = c / g;
	auto res = ExtGCD(a / g, b / g);
	return { res.first * k, res.second * k };
}

pii CRT(pii a, pii b) {
	if (a.second == -1 || b.second == -1) return { -1, -1 };
	if ((b.first - a.first) % gcd(a.second, b.second)) return { -1, -1 };
	int y = Sol(a.second, b.second, b.first - a.first).first;
	y = (y % b.second + b.second) % b.second;
	int x = (a.second * y + a.first);
	int l = lcm(a.second, b.second);
	x = (x % l + l) % l;
	return { x, l };
}

Lucas<97> L1;
Lucas<1031> L2;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, m; cin >> n >> m;
		if (n == 0 && m == 1) cout << 1 << '\n';
		else if (m == 1 || n - 1 < m - 2) cout << 0 << '\n';
		else cout << CRT({ L1(n - 1, m - 2), 97 }, { L2(n - 1, m - 2), 1031 }).first << '\n';
	}
}