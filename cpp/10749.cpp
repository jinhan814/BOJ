#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using Info = tuple<int, int, int>;

struct UnionFind {
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a ^ b) par[a] += par[b], par[b] = a;
    }
    bool Check(int a, int b) {
        a = Find(a), b = Find(b);
        return a != b;
    }
};

int main() {
	fastio;
	int64_t n, ans = 0; cin >> n;
	vector<int> v(n);
	for (auto& i : v) cin >> i;
	sort(v.begin(), v.end());

    priority_queue<Info> PQ; UnionFind UF(n);
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) PQ.push({ v[i] ^ v[j], i, j });
    for (int i = 1; i < n; i++) {
        while (!UF.Check(get<1>(PQ.top()), get<2>(PQ.top()))) PQ.pop();
        ans += get<0>(PQ.top());
        UF.Union(get<1>(PQ.top()), get<2>(PQ.top()));
        PQ.pop();
    }
    cout << ans << '\n';
}