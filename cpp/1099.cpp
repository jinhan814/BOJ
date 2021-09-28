#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

int main() {
	fastio;
	string s, v[50]; cin >> s;
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i];

	auto IsValid = [&](int idx, const string& cur) -> bool {
		if (idx < 0 || idx + cur.size() > s.size()) return 0;
		int cnt[26]{};
		for (int i = 0; i < cur.size(); i++) {
			cnt[s[idx + i] - 'a']++;
			cnt[cur[i] - 'a']--;
		}
		for (int i = 0; i < 26; i++) if (cnt[i]) return 0;
		return 1;
	};

	auto GetScore = [&](int idx, const string& cur) -> int {
		if (!IsValid(idx, cur)) return -1;
		int ret = 0;
		for (int i = 0; i < cur.size(); i++)
			if (s[idx + i] != cur[i]) ret++;
		return ret;
	};

	vector<int> DP(s.size() + 1, -1);
	auto DFS = [&](int idx, auto&& DFS) -> int {
		if (idx == 0) return 0;
		auto& ret = DP[idx];
		if (ret != -1) return ret; ret = INF;
		for (int i = 0; i < n; i++) {
			const int t = GetScore(idx - v[i].size(), v[i]);
			if (t != -1) ret = min(ret, DFS(idx - v[i].size(), DFS) + t);
		}
		return ret;
	};
	int ans = DFS(s.size(), DFS);
	cout << (ans == INF ? -1 : ans) << '\n';
}