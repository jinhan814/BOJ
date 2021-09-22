#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define all(v) (v).begin(), (v).end()
#define compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())
#define IDX(v, x) (lower_bound(all(v), x) - (v).begin() + 1)

constexpr int MOD = 1e9 + 7;
inline int ADD(int a, int b) { return (a += b) >= MOD ? a - MOD : a; }
inline int SUB(int a, int b) { return (a -= b) < 0 ? a + MOD : a; }

struct Fenwick {
	vector<int> tree; int sz;
	Fenwick(int sz = 0) : tree(sz + 1), sz(sz) {}
	void Update(int i, int val) {
		for (; i <= sz; i += i & -i) tree[i] = ADD(tree[i], val);
	}
	int Query(int i) {
		int ret = 0;
		for (; i; i -= i & -i) ret = ADD(ret, tree[i]);
		return ret;
	}
};

int n, m, k, board[751][751];
vector<int> I[750 * 750 + 1];
Fenwick FT[750 * 750 + 1];

void InitColor() {
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		I[board[i][j]].push_back(j);
	for (int i = 1; i <= k; i++) compress(I[i]);
}

void InitFT() {
	FT[0] = Fenwick(m);
	for (int i = 1; i <= k; i++) FT[i] = Fenwick(I[i].size());
}

inline int GetDP(int x, int y) {
	if (x == n && y == m) return 1;
	const int color = board[x][y];
	const int idx = IDX(I[color], y);
	int sum = SUB(FT[0].Query(m), FT[0].Query(y));
	int k_sum = SUB(FT[color].Query(I[color].size()), FT[color].Query(idx));
	return SUB(sum, k_sum);
}

int Sol() {
	for (int i = n; i >= 1; i--) {
		for (int j = 1; j <= m; j++) {
			const int color = board[i][j];
			const int idx = IDX(I[color], j);
			const int DP = GetDP(i, j);
			FT[0].Update(j, DP);
			FT[color].Update(idx, DP);
			if (i == 1 && j == 1) return DP;
		}
	}
}

int main() {
	fastio;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> board[i][j];
	InitColor(); InitFT();
	cout << Sol() << '\n';
}