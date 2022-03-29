#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

int n, I[200'000];
i64 s, T[200'000], H[200'000];
priority_queue<i64> PQ;

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> T[i] >> H[i];
	iota(I, I + n, 0);
	sort(I, I + n, [&](int a, int b) { return H[a] < H[b]; });
	for (int i = 0; i < n; i++) {
		const i64 t = T[I[i]];
		const i64 h = H[I[i]];
		if (s + t <= h) PQ.push(t), s += t;
		else if (PQ.size() && PQ.top() > t) s -= PQ.top(), PQ.pop(), PQ.push(t), s += t;
	}
	cout << PQ.size() << '\n';
}