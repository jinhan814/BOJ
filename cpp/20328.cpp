#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct State {
	char v[2][2];
	State() : v{ 0, 2, 1, 3 } {};
	void Flip(bool is_v) {
		if (is_v) swap(v[0][0], v[1][0]), swap(v[0][1], v[1][1]);
		else swap(v[0][0], v[0][1]), swap(v[1][0], v[1][1]);
	}
	void Rotate(bool is_cw) {
		if (is_cw) swap(v[0][0], v[0][1]), swap(v[1][0], v[1][1]), swap(v[0][0], v[1][1]);
		else swap(v[0][0], v[0][1]), swap(v[1][0], v[1][1]), swap(v[0][1], v[1][0]);
	}
};

int n, q;
int v[1 << 10][1 << 10];
int w[1 << 10][1 << 10];
State s[11];

void Query1(int k) { for (int i = 1; i <= k; i++) s[i].Flip(1); }
void Query2(int k) { for (int i = 1; i <= k; i++) s[i].Flip(0); }
void Query3(int k) { for (int i = 1; i <= k; i++) s[i].Rotate(1); }
void Query4(int k) { for (int i = 1; i <= k; i++) s[i].Rotate(0); }
void Query5(int k) { for (int i = k + 1; i <= n; i++) s[i].Flip(1); }
void Query6(int k) { for (int i = k + 1; i <= n; i++) s[i].Flip(0); }
void Query7(int k) { for (int i = k + 1; i <= n; i++) s[i].Rotate(1); }
void Query8(int k) { for (int i = k + 1; i <= n; i++) s[i].Rotate(0); }

void Init(int k, int vx, int vy, int wx, int wy) {
	if (k == 0) { w[wx][wy] = v[vx][vy]; return; }
	const int sz = 1 << k - 1;
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) {
		const int nvx = vx + (s[k].v[i][j] & 1) * sz;
		const int nvy = vy + (s[k].v[i][j] >> 1 & 1) * sz;
		Init(k - 1, nvx, nvy, wx + i * sz, wy + j * sz);
	}
}

void Print() {
	for (int i = 0; i < 1 << n; i++) {
		for (int j = 0; j < 1 << n; j++)
			cout << w[i][j] << ' ';
		cout << '\n';
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
		if (t == 1) Query1(k);
		else if (t == 2) Query2(k);
		else if (t == 3) Query3(k);
		else if (t == 4) Query4(k);
		else if (t == 5) Query5(k);
		else if (t == 6) Query6(k);
		else if (t == 7) Query7(k);
		else if (t == 8) Query8(k);
	}
	Init(n, 0, 0, 0, 0);
	Print();
}