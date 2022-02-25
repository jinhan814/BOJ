#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct State {
	char v[2][2];
	State() : v{ 0, 2, 1, 3 } {};
	void F(int n) {
		switch (n) {
		case 1: swap(v[0][0], v[1][0]), swap(v[0][1], v[1][1]); break;
		case 2: swap(v[0][0], v[0][1]), swap(v[1][0], v[1][1]); break;
		case 3: swap(v[0][0], v[0][1]), swap(v[1][0], v[1][1]), swap(v[0][0], v[1][1]); break;
		case 4: swap(v[0][0], v[0][1]), swap(v[1][0], v[1][1]), swap(v[0][1], v[1][0]); break;
		}
	}
};

int n, q;
int v[1 << 10][1 << 10];
int w[1 << 10][1 << 10];
State s[11];

void Query(int t, int k) {
	if (t <= 4) for (int i = 1; i <= k; i++) s[i].F(t);
	else for (int i = n; i > k; i--) s[i].F(t - 4);
}

void Init(int k, int vx, int vy, int wx, int wy) {
	if (k == 0) { w[wx][wy] = v[vx][vy]; return; }
	const int sz = 1 << k - 1;
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) {
		const int nvx = vx + (s[k].v[i][j] & 1) * sz;
		const int nvy = vy + (s[k].v[i][j] >> 1 & 1) * sz;
		Init(k - 1, nvx, nvy, wx + i * sz, wy + j * sz);
	}
}

int main() {
	fastio;
	cin >> n >> q;
	for (int i = 0; i < 1 << n; i++) {
		for (int j = 0; j < 1 << n; j++)
			cin >> v[i][j];
	}
	while (q--) {
		int t, k; cin >> t >> k;
		Query(t, k);
	}
	Init(n, 0, 0, 0, 0);
	for (int i = 0; i < 1 << n; i++) {
		for (int j = 0; j < 1 << n; j++)
			cout << w[i][j] << ' ';
		cout << '\n';
	}
}