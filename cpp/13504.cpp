#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Trie {
private:
	struct TrieNode { int nxt[2]{}, cnt = 0; };
	vector<TrieNode> node;
public:
	Trie() : node(1) { Push(0); }
	void Push(int x) {
		int cur = 0;
		for (int i = 31; i-- > 0;) {
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
		for (int i = 31; i-- > 0;) {
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
	int N; cin >> N;
	while (N--) {
		int n, P = 0, mx = 0; cin >> n;
		Trie T;
		while (n--) {
			int x; cin >> x; P ^= x;
			mx = max(mx, T(P));
			T.Push(P);
		}
		cout << mx << '\n';
	}
}