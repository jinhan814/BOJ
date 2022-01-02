#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Fenwick {
	vector<int> tree; int sz;
	Fenwick(int sz) : sz(sz), tree(sz + 1) {}
	void Update(int i, int val) {
		for (; i <= sz; i += i & -i) tree[i] += val;
	}
	int Query(int i) {
		int ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int Kth(int k) {
		int ret = 0;
		for (int i = 20; ~i; i--) {
			int t = ret | 1 << i;
			if (t <= sz && tree[t] < k) k -= tree[ret = t];
		}
		return ret + 1;
	}
};

vector<int> Josephus(int n, int k) {
	vector<int> ret; Fenwick FT(n);
	for (int i = 1; i <= n; i++) FT.Update(i, 1);
	for (int i = n, cur = n; i; i--) {
		const int t = FT.Query(cur);
		if (k % i == 0) cur = FT.Kth(t ? t : i);
		else if (i - t >= k % i) cur = FT.Kth(t + k % i);
		else cur = FT.Kth(k % i - (i - t));
		FT.Update(cur, -1), ret.push_back(cur);
	}
	return ret;
}

void Print(const vector<int>& v) {
	cout << '<';
	for (int i = 0; i + 1 < v.size(); i++) cout << v[i] << ", ";
	cout << v.back() << '>' << '\n';
}

int main() {
	fastio;
	int n, k; cin >> n >> k;
	auto res = Josephus(n, k);
	Print(res);
}