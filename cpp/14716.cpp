#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

template<size_t sz>
struct UnionFind {
    int par[sz];
    UnionFind() { memset(par, -1, sizeof par); }
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a == b) return;
        par[a] += par[b], par[b] = a;
    }
};

int n, m, cnt, v[250][250];
UnionFind<250 * 250> UF;

int main() {
	fastio;
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> v[i][j];

    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        if (!v[i][j]) continue;
        for (int k = 0; k < 8; k++) {
            int nx = i + "10001222"[k] - '1';
            int ny = j + "22100012"[k] - '1';
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (v[nx][ny]) UF.Union(i * m + j, nx * m + ny);
        }
    }

    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
        if (v[i][j] && i * m + j == UF.Find(i * m + j)) cnt++;
    cout << cnt << '\n';
}