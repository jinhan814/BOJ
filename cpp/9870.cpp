#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = int(1e9) + 7;
int adj[200][200];

int main() {
	fastio;
    int n, m, k, q; cin >> n >> m >> k >> q;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        if (i ^ j) adj[i][j] = INF;
    }
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c; --a, --b;
        adj[a][b] = min(adj[a][b], c);
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (adj[i][j] > adj[i][k] + adj[k][j])
                    adj[i][j] = adj[i][k] + adj[k][j];

    int64_t t1 = 0, t2 = 0;
    while (q--) {
        int a, b, mn = INF; cin >> a >> b; --a, --b;
        for (int i = 0; i < k; i++) {
            if (adj[a][i] == INF || adj[i][b] == INF) continue;
            mn = min(mn, adj[a][i] + adj[i][b]);
        }
        if (mn != INF) t1++, t2 += mn;
    }
    cout << t1 << '\n' << t2 << '\n';
}