#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

i64 Sol(const vector<int>& v) {
	i64 mn = 0;
	priority_queue<int> PQ;
	for (int i = 0; i < v.size(); i++) {
		const int dx = i - 1;
		if (PQ.empty() || PQ.top() + dx <= v[i]) {
			PQ.push(v[i] - dx);
		}
		else {
			mn += PQ.top() + dx - v[i];
			PQ.pop();
			PQ.push(v[i] - dx);
			PQ.push(v[i] - dx);
		}
	}
	return mn;
}

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << Sol(v) << '\n';
}