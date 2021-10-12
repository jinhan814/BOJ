#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct TrieNode {
	int nxt[26], idx;
	TrieNode() : nxt{}, idx() {}
};

struct Trie {
	vector<TrieNode> node;
	Trie() : node(1) {}

	void Add(const string& s, const int idx) {
		int cur = 0;
		for (const auto& c : s) {
			if (node[cur].nxt[c - 'A'] == 0) {
				node[cur].nxt[c - 'A'] = node.size();
				node.push_back(TrieNode());
			}
			cur = node[cur].nxt[c - 'A'];
		}
		node[cur].idx = idx;
	}
} T;

int n, q, visited[4][4];
string s[300'001], board[4];
vector<int> v;

void DFS(int x, int y, int pos) {
	if (T.node[pos].nxt[board[x][y] - 'A'] == 0) return;
	pos = T.node[pos].nxt[board[x][y] - 'A'], visited[x][y] = 1;
	if (T.node[pos].idx) v.push_back(T.node[pos].idx);
	for (int k = 0; k < 8; k++) {
		int nx = x + "10001222"[k] - '1';
		int ny = y + "22100012"[k] - '1';
		if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
		if (visited[nx][ny]) continue;
		DFS(nx, ny, pos);
	}
	visited[x][y] = 0;
}

int GetScore(int n) {
	return "00011235;"[n] - '0';
}

int main() {
	fastio;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i], T.Add(s[i], i);
	cin >> q;
	while (q--) {
		v.clear();
		for (int i = 0; i < 4; i++) cin >> board[i];
		for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) DFS(i, j, 0);
		sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
		int score = 0, cnt = 0; string mx;
		for (const auto& i : v) {
			score += GetScore(s[i].size()), cnt++;
			if (mx.size() < s[i].size() || mx.size() == s[i].size() && mx > s[i]) mx = s[i];
		}
		cout << score << ' ' << mx << ' ' << cnt << '\n';
	}
}