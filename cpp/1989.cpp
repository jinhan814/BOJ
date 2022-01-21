#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

struct UnionFind {
    vector<int> par, st, sum;
    UnionFind(int n) : par(n, -1), sum(n) {}
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a == b) return;
        if (a > b) swap(a, b);
        par[a] += par[b], par[b] = a;
        sum[a] += sum[b];
    }
    int GetSum(int x) { return sum[Find(x)]; }
    int GetLeft(int x) { return Find(x); }
    int GetRight(int x) { return x = Find(x), x - par[x] - 1; }
};

int32_t main() {
    fastio;
    int n; cin >> n;
    vector<int> v(n), w(n); iota(w.begin(), w.end(), 0);
    for (auto& i : v) cin >> i;
    sort(w.begin(), w.end(), [&v](int a, int b) { return v[a] > v[b]; });

    int mx = -1, l, r;
    UnionFind UF(n); UF.sum = v;
    for (const auto& i : w) {
        if (i && v[i - 1] >= v[i]) UF.Union(i - 1, i);
        if (i + 1 < n && v[i] <= v[i + 1]) UF.Union(i, i + 1);
        auto res = UF.GetSum(i) * v[i];
        if (mx < res) mx = res, l = UF.GetLeft(i) + 1, r = UF.GetRight(i) + 1;
    }
    cout << mx << '\n' << l << ' ' << r << '\n';
}