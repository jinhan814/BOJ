#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

/* BigInt, UnionFind */

string Add(const string& a, const string& b) {
	string ret(max(a.size(), b.size()), '0');
	bool carry = 0;
	for (int i = 0; i < ret.size(); i++) {
		int temp = carry; carry = 0;
		if (i < a.size()) temp += a[a.size() - i - 1] - '0';
		if (i < b.size()) temp += b[b.size() - i - 1] - '0';
		if (temp >= 10) carry = 1, temp -= 10;
		ret[ret.size() - i - 1] = temp + '0';
	}
	if (carry) ret.insert(ret.begin(), '1');
	return ret;
}

string Mul(const string& a, const string& b) {
	string ret = "0";
	for (int i = 0; i < b.size(); i++) {
		string s = a;
		int carry = 0;
		for (int j = a.size() - 1; j >= 0; j--) {
			int temp = carry; carry = 0;
			temp += (a[j] - '0') * (b[b.size() - i - 1] - '0');
			if (temp >= 10) carry = temp / 10, temp %= 10;
			s[j] = temp + '0';
		}
		if (carry > 0) s.insert(s.begin(), carry + '0');
		s += string(i, '0');
		ret = Add(ret, s);
	}
	return ret;
}

struct UnionFind { // -1 ver.
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a ^ b) par[a] += par[b], par[b] = a;
    }
    int Cnt(int x) { return -par[Find(x)]; }
};

/* Solution */

int n, m;
int dfs_cnt, dfs_order[20'001];
int par[20'001];
int dep[20'001];
int DP[20'001];
vector<int> cycle, adj[20'001];
bitset<20'001> visited;

void DFS1(int cur, int prv) {
	dfs_order[cur] = ++dfs_cnt;
	par[cur] = prv;
	dep[cur] = dep[prv] + 1;
	for (const auto& nxt : adj[cur]) {
		if (nxt == prv) continue;
		if (!dfs_order[nxt]) DFS1(nxt, cur);
		else if (dfs_order[nxt] < dfs_order[cur]) DP[cur]++, DP[nxt]--;
	}
}

int DFS2(int cur) {
	int& ret = DP[cur];
	for (const auto& nxt : adj[cur]) {
		if (par[nxt] != cur) continue;
		ret += DFS2(nxt);
	}
	return ret;
}

void GetCycle(int cur) {
	visited[cur] = 1;
	for (const auto& nxt : adj[cur]) {
		if (par[cur] == nxt) continue;
		if (!visited[nxt]) GetCycle(nxt);
		else if (dfs_order[nxt] < dfs_order[cur]) {
			cycle.push_back(dep[cur] - dep[nxt] + 1);
		}
	}
}

string GetAns() {
	string ret = "1";
	for (const auto& i : cycle) ret = Mul(ret, to_string(i + 1));
	return ret;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int k, a, b; m-- && cin >> k >> a;) {
		for (; --k && cin >> b;) {
			adj[a].push_back(b);
			adj[b].push_back(a);
			a = b;
		}
	}
	DFS1(1, 0), DFS2(1);
	if (dfs_cnt != n || *max_element(DP + 1, DP + n + 1) > 1) {
		cout << 0 << '\n';
	}
	else {
		GetCycle(1);
		cout << GetAns() << '\n';
	}
}