#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

constexpr int MOD = 1'000'000'007;
constexpr int INV = 500'000'004;

struct Matrix {
	int v[20][20];
	Matrix() : v{} {}
	Matrix(int j) : v{} {
		for (int i = 0; i < 20; i++) v[i][i] = 1;
		for (int i = 0; i <= j; i++) v[i][j]++;
	}
	Matrix(int j, bool inv) : v{} {
		for (int i = 0; i < 20; i++) v[i][i] = 1;
		for (int i = 0; i < j; i++) v[i][j] = MOD - INV;
		v[j][j] = INV;
	}
	const Matrix operator* (const Matrix& M) const {
		Matrix ret;
		for (int i = 0; i < 20; i++) for (int j = i; j < 20; j++) {
			for (int k = i; k <= j; k++) {
				ret.v[i][j] += (i64)v[i][k] * M.v[k][j] % MOD;
				if (ret.v[i][j] >= MOD) ret.v[i][j] -= MOD;
			}
		}
		return ret;
	}
};

Matrix P[50'001];
Matrix I[50'001];

int main() {
	fastio;
	int n, k; cin >> n >> k;
	P[0] = I[0] = Matrix(-1);
	for (int i = 1; i <= n; i++) {
		int t; cin >> t;
		P[i] = P[i - 1] * Matrix(t - 1);
		I[i] = Matrix(t - 1, 1) * I[i - 1];
	}
	int q; cin >> q;
	while (q--) {
		int l, r, res = 0; cin >> l >> r;
		for (int i = 0; i < 20; i++) for (int j = i; j < 20; j++) {
			res += (i64)I[l - 1].v[0][i] * P[r].v[i][j] % MOD;
			if (res >= MOD) res -= MOD;
		}
		cout << res << '\n';
	}
}