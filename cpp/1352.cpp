#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

string Sol(int n) {
	vector<int> v, ans; bool flag = 0;

	auto DFS = [&](auto&& DFS) -> void {
		if (flag) return;
		int sum = reduce(v.begin(), v.end());
		if (sum >= n) {
			if (sum == n) ans = v, flag = 1;
			return;
		}
		int prev = v.size() ? v.back() : 0;
		for (int i = sum + 1; i >= prev + 1; i--) {
			v.push_back(i);
			DFS(DFS);
			v.pop_back();
		}
	};
	DFS(DFS);

	auto Construct = [&](const vector<int>& v) -> string {
		string ret(n, ' '), t;
		for (int i = 0, j = 0; i < v.size(); i++, j++) {
			ret[v[i] - 1] = 'A' + j;
			t += string(v[i] - 1, 'A' + j);
		}
		for (int i = 0, j = 0; i < n; i++) {
			if (ret[i] != ' ') continue;
			ret[i] = t[j++];
		}
		return ret;
	};

	return flag ? Construct(ans) : "-1";
}

int main() {
	fastio;
	int n; cin >> n;
	cout << Sol(n) << '\n';
}