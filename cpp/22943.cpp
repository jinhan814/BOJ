#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bitset<100'000> B;
vector<int> p;
int k, m, check[10];

void Sieve() {
	B.set(); B[0] = B[1] = 0;
	for (int i = 2; i * i < 100'000; i++) {
		if (!B[i]) continue;
		for (int j = i * i; j < 100'000; j += i) B[j] = 0;
	}
	for (int i = 2; i < 100'000; i++) if (B[i]) p.push_back(i);
}

bool Check1(int n) {
	for (int i : p) {
		if (2 * i >= n) break;
		if (B[n - i]) return 1;
	}
	return 0;
}

bool Check2(int n) {
	for (int i : p) {
		if (i * i > n) break;
		if (n % i == 0 && B[n / i]) return 1;
	}
	return 0;
}

int DFS(int cur, int dep) {
	if (dep == k) {
		if (!Check1(cur)) return 0;
		while (cur && cur % m == 0) cur /= m;
		return Check2(cur);
	}
	int ret = 0; cur *= 10;
	for (int i = !dep; i < 10; i++) { 
		if (check[i]) continue;
		check[i] = 1;
		ret += DFS(cur + i, dep + 1);
		check[i] = 0;
	}
	return ret;
}

int main() {
	fastio;
	Sieve();
	cin >> k >> m;
	cout << DFS(0, 0) << '\n';
}