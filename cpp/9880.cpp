#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

struct cmp {
	bool operator() (const pii& a, const pii& b) const {
		return a.second > b.second;
	}
};

int main() {
	fastio;
	int n, cnt = 0; cin >> n;
	priority_queue<pii, vector<pii>, cmp> PQ;
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		PQ.push({ a, b });
	}

	for (int t1 = -1, t2 = -1; PQ.size(); PQ.pop()) {
		if (t1 > t2) swap(t1, t2);
		if (PQ.top().first < t1);
		else if (PQ.top().first < t2) t1 = PQ.top().second, cnt++;
		else t2 = PQ.top().second, cnt++;
	}

	cout << cnt << '\n';
}