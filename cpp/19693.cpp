#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

i64 Sol(const vector<int>& v, const i64 h) {
	i64 mn = 0;
	priority_queue<i64> L;
	priority_queue<i64, vector<i64>, greater<>> R;
	L.push(v[0]), R.push(v[0]);
	for (int i = 1; i < v.size(); i++) {
		const i64 optl = L.top() - i * h;
		const i64 optr = R.top() + i * h;
		if (v[i] < optl) {
			L.push(v[i] + i * h);
			L.push(v[i] + i * h);
			L.pop();
			R.push(optl - i * h);
			mn += optl - v[i];
		}
		else if (v[i] > optr) {
			R.push(v[i] - i * h);
			R.push(v[i] - i * h);
			R.pop();
			L.push(optr + i * h);
			mn += v[i] - optr;
		}
		else {
			L.push(v[i] + i * h);
			R.push(v[i] - i * h);
		}
	}
	return mn;
}

int main() {
	fastio;
	int n, h; cin >> n >> h;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << Sol(v, h) << '\n';
}