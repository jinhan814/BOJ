#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

template<typename T, typename F>
struct SegTree {
    const size_t sz; const T ID; F f;
    vector<T> tree;
    SegTree(size_t n, T ID = T{}) : SegTree(n, ID, F{}) {}
    explicit SegTree(size_t n, T ID, const F& f) :
        sz(Log2(n)), ID(ID), f(f),
        tree(sz << 1, ID) {}
    static size_t Log2(size_t n) {
        n--;
        for (int i = 0; i < 5; i++) n |= n >> (1 << i);
        return n + 1;
    }
    void Update(int i, T val) {
        --i |= sz; tree[i] = val;
        while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }
    T Query(int l, int r) const {
        T L = ID, R = ID; --l |= sz, --r |= sz;
        while (l <= r) {
            if (l & 1) L = f(L, tree[l++]);
            if (~r & 1) R = f(tree[r--], R);
            l >>= 1, r >>= 1;
        }
        return f(L, R);
    }
};

struct Node {
    int l, r, mx; bool flag;
    Node(int t = 0) { l = r = mx = flag = t; }
    Node(int l, int r, int mx, bool flag) : l(l), r(r), mx(mx), flag(flag) {}
};

struct Merge {
    Node operator() (const Node& a, const Node& b) const {
        Node ret;
        ret.l = a.flag ? a.l + b.l : a.l;
        ret.r = b.flag ? a.r + b.r : b.r;
        ret.mx = max({ a.mx, b.mx, a.r + b.l });
        ret.flag = a.flag && b.flag;
        return ret;
    }
};

struct Query { int l, r, w; } Q[100'001];
int n, q, v[100'001], idx[100'001];
int lo[100'001], hi[100'001];

void PBS() {
    iota(idx, idx + n + 1, 0);
    sort(idx, idx + n + 1, [&](int a, int b) { return v[a] > v[b]; });
    for (int i = 1; i <= q; i++) hi[i] = 1e9 + 7;
    while (1) {
        vector<pii> I;
        for (int i = 1; i <= q; i++) if (lo[i] + 1 < hi[i]) I.push_back({ lo[i] + hi[i] >> 1, i });
        if (I.empty()) break;
        sort(I.rbegin(), I.rend());
        SegTree<Node, Merge> ST(n);
        for (int i = 0, j = 0; i <= n && j < I.size(); i++) {
            while (j < I.size() && I[j].first > v[idx[i]]) {
                const auto [mid, p] = I[j++];
                if (ST.Query(Q[p].l, Q[p].r).mx >= Q[p].w) lo[p] = mid;
                else hi[p] = mid;
            }
            if (idx[i]) ST.Update(idx[i], 1);
        }
    }
}

int main() {
    fastio;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> v[i];
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> Q[i].l >> Q[i].r >> Q[i].w;
    PBS();
    for (int i = 1; i <= q; i++) cout << lo[i] << '\n';
}