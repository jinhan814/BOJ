#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

struct UnionFind { // -1 ver.
    vector<int> par, v;
    UnionFind(int n) : par(n, -1), v(n) {}
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a ^ b) par[a] += par[b], par[b] = a, v[a] ^= v[b];
    }
};

struct Info { int x, y, val; };

int n, m, v[1000][1000];

int32_t main() {
    fastio;
    cin >> n >> m;
    UnionFind UF(n * m); vector<Info> I;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        int t; cin >> t;
        I.push_back({ i, j, t });
    }
    sort(I.begin(), I.end(), [](const Info& a, const Info& b) { return a.val > b.val; });

    int ans = 0, score = 0;
    for (const auto& [x, y, val] : I) {
        UF.v[x * m + y] = v[x][y] = val; set<int> S;
        for (int k = 0; k < 4; k++) {
            int nx = x + "1012"[k] - '1';
            int ny = y + "2101"[k] - '1';
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (v[nx][ny]) S.insert(UF.Find(nx * m + ny));
        }
        for (const auto& i : S) score -= UF.v[i];
        for (int k = 0; k < 4; k++) {
            int nx = x + "1012"[k] - '1';
            int ny = y + "2101"[k] - '1';
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (v[nx][ny]) UF.Union(x * m + y, nx * m + ny);
        }
        score += UF.v[UF.Find(x * m + y)];
        ans = max(ans, score);
    }
    cout << ans << '\n';
}