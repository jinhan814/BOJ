#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

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

int n; string s;
vector<int> adj[100'000];
UnionFind UF(100'000);

int main() {
	fastio;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b; --a, --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cin >> s;

    for (int i = 0; i < n; i++) for (const auto& j : adj[i]) {
        if (s[i] == 'R' && s[j] == 'R') UF.Union(i, j);
    }

    int64_t ans = 0;
    for (int i = 0; i < n; i++) if (s[i] == 'B')
        for (const auto& j : adj[i]) if (s[j] == 'R')
            ans += UF.Cnt(j);
    cout << ans << '\n';
}