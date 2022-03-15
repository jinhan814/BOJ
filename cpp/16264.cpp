#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int sq = 400;
using i64 = long long;

class Query { // reference : https://www.acmicpc.net/source/27941653
public:
	int st, en;
	Query(int st, int en) : st(st), en(en) {}
	bool operator< (const Query& i) const { return pr < i.pr; }
private:
	i64 pr = ConvHilbert(st, en);
	static i64 ConvHilbert(int x, int y) {
		i64 ret = 0;
		for (int i = 17, cx, cy; ~i; i--) {
			cx = x >> i & 1, cy = y >> i & 1;
			ret = ret << 2 | cx << 1 | cx ^ cy;
			cy || (swap(x, y), cx) && (x = ~x, y = ~y);
		}
		return ret;
	}
};

void Solve() {
	// 1. input
	int n; cin >> n;
	vector<int> P(n + 1);
	for (int i = 1; i <= n; i++) cin >> P[i];
	for (int i = 1; i <= n; i++) P[i] += P[i - 1];
	int q; cin >> q;
	vector<Query> Q; Q.reserve(q);
	for (int i = 0; i < q; i++) {
		int l, r; cin >> l >> r; --l;
		Q.push_back(Query(l, r));
	}
	sort(Q.begin(), Q.end());

	// 2.
	const int b_sz = n / sq;
	vector<int> cnt(n + 1), bucket(b_sz + 1);
	vector<list<int>> L(2 * n + 1);
	auto Push = [&](int idx, bool flag) -> void {
		auto& v = L[P[idx] + n];
		if (v.size()) {
			const int val = v.back() - v.front();
			cnt[val]--, bucket[val / sq]--;
		}
		if (flag) v.push_back(idx);
		else v.push_front(idx);
		const int val = v.back() - v.front();
		cnt[val]++, bucket[val / sq]++;
	};
	auto Pop = [&](int idx, bool flag) -> void {
		auto& v = L[P[idx] + n];
		const int val = v.back() - v.front();
		cnt[val]--, bucket[val / sq]--;
		if (flag) v.pop_back();
		else v.pop_front();
		if (v.size()) {
			const int val = v.back() - v.front();
			cnt[val]++, bucket[val / sq]++;
		}
	};
	auto Sol = [&]() -> int {
		for (int i = b_sz; ~i; i--) {
			if (!bucket[i]) continue;
			for (int j = sq - 1; ~j; j--) {
				if (i * sq + j > n || !cnt[i * sq + j]) continue;
				return i * sq + j;
			}
		}
	};

	// 3. mo's
	i64 res = 0; int st = 0, en = -1;
	for (const auto& i : Q) {
		if (en < i.st || i.en < st) {
			while (st <= en) Pop(st++, 0);
			st = i.st, en = st - 1;
		}
		while (i.st < st) Push(--st, 0);
		while (i.st > st) Pop(st++, 0);
		while (i.en > en) Push(++en, 1);
		while (i.en < en) Pop(en--, 1);
		res += Sol();
	}
	cout << res << '\n';
}

int main() {
	fastio;
	int N; cin >> N;
	while (N--) Solve();
}