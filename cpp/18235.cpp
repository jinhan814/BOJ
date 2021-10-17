#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, a, b;
bitset<500'001> A, B;

int Sol() {
	queue<int> Q1, Q2; Q1.push(a), Q2.push(b);
	for (int i = 1; i < 20; i++) {
		const int delta = 1 << i - 1; A.reset(), B.reset();
		for (int sz = Q1.size(); sz-- > 0;) {
			auto cur = Q1.front(); Q1.pop();
			for (int nxt : { cur - delta, cur + delta }) {
				if (1 <= nxt && nxt <= n && !A[nxt]) Q1.push(nxt), A[nxt] = 1;
			}
		}
		for (int sz = Q2.size(); sz-- > 0;) {
			auto cur = Q2.front(); Q2.pop();
			for (int nxt : { cur - delta, cur + delta }) {
				if (1 <= nxt && nxt <= n && !B[nxt]) Q2.push(nxt), B[nxt] = 1;
				if (1 <= nxt && nxt <= n && A[nxt]) return i;
			}
		}
	}
	return -1;
}

int main() {
	fastio;
	cin >> n >> a >> b;
	cout << Sol() << '\n';
}