#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Fenwick {
    vector<int> tree; int sz;
    Fenwick(int sz) : tree(sz + 1), sz(sz) {}
    void Update(int i, int val) {
        for (; i <= sz; i += i & -i) tree[i] += val;
    }
    int Query(int i) {
        int ret = 0;
        for (; i; i -= i & -i) ret += tree[i];
        return ret;
    }
};

int n, v[100'001], w[100'001];

bool Check(int mid) {
    Fenwick FT(n + 1); FT.Update(n + 1, 1);
    vector<int> pSum(n + 1);
    for (int i = 1; i <= n; i++) pSum[i] = pSum[i - 1] + (w[i] > mid);
    for (int i = n; i >= 1; i--) {
        bool DP = 0;
        if (w[i] <= mid) DP |= FT.Query(i + 1) - FT.Query(i);
        const int l = i + v[i] - 1;
        const int r = lower_bound(pSum.begin() + i, pSum.end(), pSum[i] + v[i]) - pSum.begin() - 1;
        if (l <= r) DP |= FT.Query(r + 1) - FT.Query(l);
        FT.Update(i, DP);
    }
    return FT.Query(1);
}

int main() {
    fastio;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 1; i <= n; i++) cin >> w[i];

    int lo = -1, hi = 100'000;
    while (lo + 1 < hi) {
        int mid = lo + hi >> 1;
        if (!Check(mid)) lo = mid;
        else hi = mid;
    }
    cout << hi << '\n';
}