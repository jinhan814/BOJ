#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 1e9 + 7;

template<size_t sz>
struct Factorial {
    array<int, sz> v;
    Factorial() { v[0] = 1; for (int i = 1; i < sz; i++) v[i] = 1LL * v[i - 1] * i % MOD; }
    const int& operator[] (int i) const { return v[i]; }
};

struct UnionFind {
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a ^ b) par[a] += par[b], par[b] = a;
    }
    int Cnt(int x) { return -par[Find(x)]; }
};

int main() {
	fastio;
    int n, res = 1; cin >> n;
    vector<string> v(n, string(n, 0)); UnionFind UF(n); Factorial<501> F;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> v[i][j], i == j && (v[i][j] = '0');
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (v[i][j] & 1 && v[j][i] & 1) v[i][i] = '1';
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (v[i][j] & 1 && v[i][i] & 1 && v[j][j] & 1) UF.Union(i, j);
    for (int i = 0; i < n; i++) {
        if (v[i][i] & 1) {
            if (UF.Find(i) != i) continue;
            res = 1LL * res * F[UF.Cnt(i) - 1] % MOD;
        }
        else {
            bool flag = 0;
            for (int j = 0; j < n; j++) if (v[i][j] & 1 && ~v[j][j] & 1) flag = 1;
            if (flag) continue;
            for (int j = 0; j < n; j++) if (v[i][j] & 1) { res = 1LL * res * UF.Cnt(j) % MOD; break; }
        }
    }
    cout << res << '\n';
}