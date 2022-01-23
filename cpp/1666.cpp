#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Info { int x1, y1, x2, y2; };

struct PQ_Info {
    int x, y, val;
    bool operator< (const PQ_Info& i) const { return y > i.y; }
};

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

template<typename T> struct Max {
    constexpr T operator() (const T& a, const T& b) const {
        return max<T>(a, b);
    }
};

int main() {
	fastio;
	// 1. input
	int n; cin >> n;
	vector<Info> v(n);
	vector<int> I; I.reserve(n << 1);
	for (auto& [x1, y1, x2, y2] : v) {
		cin >> x1 >> y1 >> x2 >> y2;
		I.push_back(x1), I.push_back(x2);
	}

	// 2. coordinate compression, sort
	sort(I.begin(), I.end()), I.erase(unique(I.begin(), I.end()), I.end());
	for (auto& [x1, y1, x2, y2] : v) {
		x1 = lower_bound(I.begin(), I.end(), x1) - I.begin() + 1;
		x2 = lower_bound(I.begin(), I.end(), x2) - I.begin() + 1;
	}
	sort(v.begin(), v.end(), [](const Info& a, const Info& b) {
		if (a.y1 != b.y1) return a.y1 < b.y1;
		return a.x1 < b.x1;
	});

	// 3. DP
    Fenwick<int, Max<int>> FT(I.size(), 0);
    priority_queue<PQ_Info> PQ;
    auto Pop = [&]() {
		auto [x, y, val] = PQ.top(); PQ.pop();
		if (FT.v[x] < val) FT.Update(x, val);
    };
    for (const auto& [x1, y1, x2, y2] : v) {
        while (PQ.size() && PQ.top().y < y1) Pop();
        PQ.push({ x2, y2, FT.Query(1, x1 - 1) + 1 });
    }
    while (PQ.size()) Pop();
    cout << FT.Query(1, I.size()) << '\n';
}