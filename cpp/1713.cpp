#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m, pos[101]{}, cnt[101]{}; cin >> n >> m;
	set<tuple<int, int, int>> S;
	for (int i = 1; i <= m; i++) {
		int t; cin >> t;
		if (pos[t]) {
			S.erase(S.find({ cnt[t], pos[t], t }));
			cnt[t]++;
			S.insert({ cnt[t], pos[t], t });
		}
		else {
			if (S.size() < n) {
				pos[t] = i, cnt[t] = 1;
				S.insert({ cnt[t], pos[t], t });
			}
			else {
				auto [pcnt, ppos, pt] = *S.begin(); S.erase(S.begin());
				pos[pt] = cnt[pt] = 0;
				pos[t] = i, cnt[t] = 1;
				S.insert({ cnt[t], pos[t], t });
			}
		}
	}
	vector<int> res;
	for (const auto& [cnt, pos, t] : S) res.push_back(t);
	sort(res.begin(), res.end());
	for (const auto& i : res) cout << i << ' '; cout << '\n';
}