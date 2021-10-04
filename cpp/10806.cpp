#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct UnionFind { // -1 ver.
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a ^ b) par[a] += par[b], par[b] = a;
    }
};

struct BCC { // edge-disjoint bcc
	int n, dfs_cnt, edge_cnt;
    vector<int> dfs_order; UnionFind UF;
    vector<tuple<int, int, int>> bridge;
    vector<vector<pair<int, int>>> adj;

    BCC(int n) :
        n(n), adj(n + 1),
        dfs_order(n + 1), UF(n + 1),
        dfs_cnt(0), edge_cnt(0) {}

    void AddEdge(int a, int b, int idx = -1) {
        if (idx == -1) idx = edge_cnt++;
        adj[a].push_back({ b, idx });
        adj[b].push_back({ a, idx });
    }

    int DFS(int cur, int prv_idx = -1) {
        int ret = dfs_order[cur] = ++dfs_cnt;
        for (const auto& [nxt, idx] : adj[cur]) {
            if (idx == prv_idx) continue;
            if (!dfs_order[nxt]) {
                const int t = DFS(nxt, idx);
                if (t > dfs_order[cur]) bridge.push_back({ cur, nxt, idx });
                else UF.Union(cur, nxt);
                ret = min(ret, t);
            }
            else ret = min(ret, dfs_order[nxt]);
        }
        return ret;
    }

    void GetBCC(bool flag = 0) {
        for (int i = 1; i <= n; i++)
            if (!dfs_order[i]) DFS(i);

        if (flag) {
            cout << '\n' << "bridge :" << '\n';
            for (auto& [a, b, idx] : bridge) cout << a << ' ' << b << ' ' << idx << '\n';

            cout << '\n' << "color :" << '\n';
            for (int i = 1; i <= n; i++) cout << UF.Find(i) << ' ';
            cout << '\n' << '\n';
        }
    }
};

int main() {
	fastio;
    int n, m; cin >> n >> m; BCC B(n);
    for (int a, b; m-- && cin >> a >> b; B.AddEdge(a, b));
    B.GetBCC();

    // n = 1
    if (B.bridge.empty()) return !(cout << 0 << '\n');

    vector<vector<int>> adj(n + 1);
    for (auto [a, b, idx] : B.bridge) {
        a = B.UF.Find(a), b = B.UF.Find(b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // n <= 3
    auto Check = [&]() -> bool {
        vector<int> leaf;
        for (int i = 1; i <= n; i++) if (adj[i].size() == 1) leaf.push_back(i);
        if (leaf.size() == 2) {
            cout << 1 << '\n';
            cout << leaf[0] << ' ' << leaf[1] << '\n';
            return 0;
        }
        if (leaf.size() == 3) {
            cout << 2 << '\n';
            cout << leaf[0] << ' ' << leaf[1] << '\n';
            cout << leaf[0] << ' ' << leaf[2] << '\n';
            return 0;
        }
        return 1;
    };
    if (!Check()) return 0;

    // n >= 4
    vector<int> DP(n + 1, -1);
    auto GetDP = [&](int cur, int prv, auto&& GetDP) -> int {
        int& ret = DP[cur];
        if (ret != -1) return ret; ret = adj[cur].size() == 1;
        for (const auto& nxt : adj[cur]) if (nxt != prv) ret += GetDP(nxt, cur, GetDP);
        return ret;
    };

    int st = 0;
    for (int i = 1; i <= n; i++) if (adj[i].size() > 2) st = i;
    GetDP(st, -1, GetDP);

    sort(adj[st].begin(), adj[st].end(), [&](int a, int b) { return DP[a] < DP[b]; });

    vector<int> leaf;
    auto DFS = [&](int cur, int prv, auto&& DFS) -> void {
        if (adj[cur].size() == 1) leaf.push_back(cur);
        for (const auto& nxt : adj[cur]) if (nxt != prv) DFS(nxt, cur, DFS);
    };
    DFS(st, -1, DFS);

    const int sz = leaf.size(), bias = sz / 2;
    cout << (sz + 1) / 2 << '\n';
	for (int i = 0; i < bias; i++) cout << leaf[i] << ' ' << leaf[i + bias] << '\n';
    if (sz & 1) cout << leaf[0] << ' ' << leaf.back() << '\n';
}