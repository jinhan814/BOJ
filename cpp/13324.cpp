#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

vector<int> Sol(const vector<int>& v) {
	priority_queue<int> PQ;
	vector<int> opt(v.size());
	for (int i = 0; i < v.size(); i++) {
		const int dx = i - 1;
		if (PQ.empty() || PQ.top() + dx <= v[i]) {
			PQ.push(v[i] - dx);
		}
		else {
			PQ.pop();
			PQ.push(v[i] - dx);
			PQ.push(v[i] - dx);
		}
		opt[i] = PQ.top() + dx;
	}
	for (int i = v.size() - 2; i >= 0; i--) opt[i] = min(opt[i], opt[i + 1] - 1);
	return opt;
}

int main() {
	fastio;
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i : Sol(v)) cout << i << '\n';
}