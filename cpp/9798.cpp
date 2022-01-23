#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

template<typename T, typename F>
struct Fenwick {
    const int n; const T ID; F f;
    vector<T> v, FT1, FT2;
    Fenwick(int n, T ID) : Fenwick(n, ID, F{}) {}
    explicit Fenwick(int n, T ID, const F& f) :
        n(n), ID(ID), f(f),
        v(n + 1, ID), FT1(n + 1, ID), FT2(n + 1, ID) {}
    void Update(int i, T val) {
        T t = v[i] = val;
        for (int j = i, l = i - 1, r = i + 1; j <= n; j += j & -j) {
            while (l > j - (j & -j)) t = f(FT1[l], t), l -= l & -l;
            while (r < j) t = f(t, FT2[r]), r += r & -r;
            FT1[j] = i ^ j ? f(t, v[j]) : t;
        }
        t = val;
        for (int j = i, l = i - 1, r = i + 1; j; j -= j & -j) {
            while (l > j) t = f(FT1[l], t), l -= l & -l;
            while (r <= n && r < j + (j & -j)) t = f(t, FT2[r]), r += r & -r;
            FT2[j] = i ^ j ? f(v[j], t) : t;
        }
    }
    T Query(int l, int r) {
        T L = ID, R = ID; int i;
        for (i = l; i + (i & -i) <= r; i += i & -i) L = f(L, FT2[i]);
        for (i = r; i - (i & -i) >= l; i -= i & -i) R = f(FT1[i], R);
        return f(f(L, v[i]), R);
    }
};

template<typename T> struct Min {
    constexpr T operator() (const T& a, const T& b) const {
        return min<T>(a, b);
    }
};

struct Info {
    int x, y, idx;
    bool operator< (const Info& i) const { return x < i.x; }
};

struct FenwickInfo {
    int y, idx;
    bool operator< (const FenwickInfo& i) const { return y < i.y; }
};

int main() {
	fastio;
    int n; cin >> n;
    vector<Info> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i].x >> v[i].y;
        v[i].idx = i;
    }
    sort(v.begin() + 1, v.end());

    Fenwick<FenwickInfo, Min<FenwickInfo>> FT(n, FenwickInfo{ INF, 0 });
    for (int i = 1; i <= n; i++) FT.Update(i, FenwickInfo{ v[i].y, i });

    vector<int> par(n + 1), l(n + 1), r(n + 1);
    auto DFS = [&](int st, int en, auto&& DFS) -> int {
        if (en < st) return 0;
        const auto idx = FT.Query(st, en).idx;
        l[idx] = DFS(st, idx - 1, DFS);
        r[idx] = DFS(idx + 1, en, DFS);
        return par[l[idx]] = par[r[idx]] = idx;
    };
    DFS(1, n, DFS);

    vector<int> rev(n + 1);
    for (int i = 1; i <= n; i++) rev[v[i].idx] = i;

    cout << "YES" << '\n';
    for (int i = 1; i <= n; i++) {
        cout << v[par[rev[i]]].idx << ' '
             << v[l[rev[i]]].idx << ' '
             << v[r[rev[i]]].idx << '\n';
    }
}