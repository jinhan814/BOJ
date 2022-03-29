#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

int n, I[250'000];
i64 s, L[250'000], D[250'000];
priority_queue<i64> PQ;

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> L[i] >> D[i];
	iota(I, I + n, 0);
	sort(I, I + n, [&](int a, int b) { return L[a] + D[a] < L[b] + D[b]; });
	for (int i = 0; i < n; i++) {
		const i64 l = L[I[i]];
		const i64 d = D[I[i]];
		if (s <= l) PQ.push(d), s += d;
		else if (PQ.size() && PQ.top() > d) s -= PQ.top(), PQ.pop(), PQ.push(d), s += d;
	}
	cout << PQ.size() << '\n';
}