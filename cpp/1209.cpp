#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

i64 Sol(const vector<int>& v) {
	i64 ret = 0; priority_queue<int> PQ;
	for (int i = 0; i < v.size(); i++) {
		if (PQ.size() && PQ.top() > v[i]) ret += PQ.top() - v[i], PQ.pop(), PQ.push(v[i]);
		PQ.push(v[i]);
	}
	return ret;
}

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = Sol(v); reverse(v.begin(), v.end());
	cout << min(res, Sol(v)) << '\n';
}