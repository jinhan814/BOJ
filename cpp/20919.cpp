#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Trie {
private:
	struct TrieNode { int nxt[2]{}, cnt = 0; };
	vector<TrieNode> node;
public:
	Trie() : node(1) {}
	void Insert(int x) {
		int cur = 0;
		for (int i = 25; i-- > 0;) {
			const bool flag = x & 1 << i;
			if (!node[cur].nxt[flag]) {
				node[cur].nxt[flag] = node.size();
				node.push_back(TrieNode());
			}
			cur = node[cur].nxt[flag];
		}
		if (node[cur].cnt) return;
		node[cur = 0].cnt++;
		for (int i = 25; i-- > 0;) {
			const bool flag = x & 1 << i;
			cur = node[cur].nxt[flag];
			node[cur].cnt++;
		}
	}
	void Erase(int x) {
		int cur = 0; node[cur].cnt--;
		for (int i = 25; i-- > 0;) {
			const bool flag = x & 1 << i;
			cur = node[cur].nxt[flag];
			node[cur].cnt--;
		}
	}
	int GetMax(int x) const {
		int ret = 0, cur = 0;
		for (int i = 25; i-- > 0;) {
			const bool flag = x & 1 << i;
			if (node[cur].nxt[!flag] && node[node[cur].nxt[!flag]].cnt) {
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
	int GetMin(int x) const {
		int ret = 0, cur = 0;
		for (int i = 25; i-- > 0;) {
			const bool flag = x & 1 << i;
			if (node[cur].nxt[flag] && node[node[cur].nxt[flag]].cnt) {
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
	size_t size() const { return node[0].cnt; }
};

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, q; cin >> n >> q; Trie T;
		while (n--) {
			int t; cin >> t;
			T.Insert(t);
		}
		while (q--) {
			int t, x; cin >> t;
			if (t == 1) cin >> x, cout << T.GetMin(x) << '\n';
			else if (t == 2) cin >> x, cout << T.GetMax(x) << '\n';
			else if (t == 3) cin >> x, T.Insert(x), cout << T.size() << '\n';
			else if (t == 4) { auto res = T.GetMin(0); cout << res << '\n'; T.Erase(res); }
			else { auto res = T.GetMax(0); cout << res << '\n'; T.Erase(res); }
		}
	}
}