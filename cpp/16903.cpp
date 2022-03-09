#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Trie {
private:
	struct TrieNode { int nxt[2]{}, cnt = 0; };
	vector<TrieNode> node;
public:
	Trie() : node(1) { Insert(0); }
	void Insert(int x) {
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
	void Erase(int x) {
		int cur = 0;
		for (int i = 30; i-- > 0;) {
			const bool flag = x & 1 << i;
			cur = node[cur].nxt[flag];
			node[cur].cnt--;
		}
	}
	int Max(int x) const {
		int ret = 0, cur = 0;
		for (int i = 30; i-- > 0;) {
			const bool flag = x & 1 << i;
			if (node[node[cur].nxt[!flag]].cnt) {
				ret = ret << 1 | 1;
				cur = node[cur].nxt[!flag];
			}
			else {
				ret = ret << 1;
				cur = node[cur].nxt[flag];
			}
		}
		return ret;
	}
};


int main() {
	fastio;
	int q; cin >> q; Trie T;
	while (q--) {
		int t, x; cin >> t >> x;
		if (t == 1) T.Insert(x);
		else if (t == 2) T.Erase(x);
		else cout << T.Max(x) << '\n';
	}
}