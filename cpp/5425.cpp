#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int p[19]{ 1 };

inline int F(int n, int i, int j) {
	int ret = n / p[i + 1] * p[i], t = n / p[i] % 10;
	if (t > j) ret += p[i];
	else if (t == j) ret += n % p[i] + 1;
	return ret;
}

inline int G(int n) {
	int ret = 0;
	for (int i = 0; i < 18; i++) for (int j = 1; j < 10; j++)
		ret += F(n, i, j) * j;
	return ret;
}

int32_t main() {
	fastio;
	for (int i = 1; i <= 18; i++) p[i] = 10 * p[i - 1];
    int N; cin >> N;
    while (N--) {
	    int a, b; cin >> a >> b;
	    cout << G(b) - (a ? G(a - 1) : 0) << '\n';
    }
}