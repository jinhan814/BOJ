/*
 * reference : https://www.acmicpc.net/source/33288297
 */

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

template<typename T>
struct KDTree {
private:
	constexpr static size_t NAIVE_THRESHOLD = 16;
	constexpr static T MAX_VALUE = numeric_limits<T>::max();
	using P = pair<T, T>; vector<P> tree;

	template<bool IsFirst = 1>
	struct Cmp {
		bool operator() (const P& a, const P& b) const {
			if constexpr (IsFirst) return a.first < b.first;
			else return a.second < b.second;
		}
	};

	T GetDist(const P& a, const P& b) const {
		return (a.first - b.first) * (a.first - b.first)
			+ (a.second - b.second) * (a.second - b.second);
	}

public:
	KDTree() = default;
	explicit KDTree(int n) : tree(n) {}
	explicit KDTree(const vector<P>& v) : tree(v) { Construct(0, v.size()); }

	template<bool IsFirst = 1>
	void Construct(int l, int r) {
		if (r - l <= NAIVE_THRESHOLD) return;
		const int m = l + r >> 1;
		nth_element(tree.begin() + l, tree.begin() + m, tree.begin() + r, Cmp<IsFirst>{});
		Construct<!IsFirst>(l, m), Construct<!IsFirst>(m + 1, r);
	}

	template<bool IsFirst = 1>
	void Query(const P& p, int l, int r, T& res) {
		if (r - l <= NAIVE_THRESHOLD) {
			for (int i = l; i < r; i++) if (p != tree[i])
				res = min(res, GetDist(p, tree[i]));
		}
		else {
			const int m = l + r >> 1;
			const T t = IsFirst ?
						p.first - tree[m].first :
						p.second - tree[m].second;
			if (p != tree[m]) res = min(res, GetDist(p, tree[m]));
			if (t < 0) {
				Query<!IsFirst>(p, l, m, res);
				if (t * t < res) Query<!IsFirst>(p, m + 1, r, res);
			}
			else {
				Query<!IsFirst>(p, m + 1, r, res);
				if (t * t < res) Query<!IsFirst>(p, l, m, res);
			}
		}
	}

	T Query(const P& p) {
		T ret = MAX_VALUE;
		Query(p, 0, tree.size(), ret);
		return ret;
	}
};

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		vector<pair<long long, long long>> v(n);
		for (auto& [a, b] : v) cin >> a >> b;
		KDTree<long long> T(v);
		for (int i = 0; i < n; i++) cout << T.Query(v[i]) << '\n';
	}
}