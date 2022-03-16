#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

struct Trie {
private:
	struct TrieNode { int nxt[2]{}, cnt = 0; };
	vector<TrieNode> node;
public:
	Trie() : node(1) {}
	void Push(int x) {
		int cur = 0;
		for (int i = 30; i-- > 0;) {
			const bool flag = x & 1 << i;
			if (!node[cur].nxt[flag]) {
				node[cur].nxt[flag] = node.size();
				node.push_back(TrieNode());
			}
			cur = node[cur].nxt[flag];
			node[cur].cnt++;
		}
	}
	int operator() (int x) const {
		int ret = 0, cur = 0;
		for (int i = 30; i-- > 0;) {
			const bool flag = x & 1 << i;
			if (node[node[cur].nxt[flag]].cnt) {
				ret = ret << 1;
				cur = node[cur].nxt[flag];
			}
			else {
				ret = ret << 1 | 1;
				cur = node[cur].nxt[!flag];
			}
		}
		return ret;
	}
};

int n, v[200'000];

i64 DFS(int l, int r, int dep) {
	if (dep < 0 || r <= l) return 0;
	if (v[l] & 1 << dep || ~v[r] & 1 << dep) return DFS(l, r, dep - 1);
	int mn = INT_MAX, pos = r; Trie T;
	while (v[pos] & 1 << dep) T.Push(v[pos--]);
	for (int i = l; i <= pos; i++) mn = min(mn, T(v[i]));
	return mn + DFS(l, pos, dep - 1) + DFS(pos + 1, r, dep - 1);
}

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v, v + n);
	cout << DFS(0, n - 1, 29) << '\n';
}