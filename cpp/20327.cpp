#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, q, v[128][128], t[128][128];

inline void C() {
	for (int i = 0; i < m; i++) memcpy(t[i], v[i], m << 2);
}

inline void F(int x1, int y1, int x2, int y2, int sz) {
	for (int i = 0; i < sz; i++) for (int j = 0; j < sz; j++)
		v[x2 + i][y2 + j] = t[x1 + i][y1 + j];
}

void Query1(int sz) {
	for (int x = 0; x < m; x += sz) for (int y = 0; y < m; y += sz)
		for (int i = 0; i < sz; i++) for (int j = 0; j < sz; j++)
			v[x + i][y + j] = t[x + (sz - 1 - i)][y + j];
}

void Query2(int sz) {
	for (int x = 0; x < m; x += sz) for (int y = 0; y < m; y += sz)
		for (int i = 0; i < sz; i++) for (int j = 0; j < sz; j++)
			v[x + i][y + j] = t[x + i][y + (sz - 1 - j)];
}

void Query3(int sz) {
	for (int x = 0; x < m; x += sz) for (int y = 0; y < m; y += sz)
		for (int i = 0; i < sz; i++) for (int j = 0; j < sz; j++)
			v[x + i][y + j] = t[x + (sz - 1 - j)][y + i];
}

void Query4(int sz) {
	for (int x = 0; x < m; x += sz) for (int y = 0; y < m; y += sz)
		for (int i = 0; i < sz; i++) for (int j = 0; j < sz; j++)
			v[x + i][y + j] = t[x + j][y + (sz - 1 - i)];
}

void Query5(int sz) {
	for (int x = 0; x < m; x += sz) for (int y = 0; y < m; y += sz)
		F(x, y, m - sz - x, y, sz);
}

void Query6(int sz) {
	for (int x = 0; x < m; x += sz) for (int y = 0; y < m; y += sz)
		F(x, y, x, m - sz - y, sz);
}

void Query7(int sz) {
	for (int x = 0; x < m; x += sz) for (int y = 0; y < m; y += sz)
		F(x, y, (y / sz) * sz, (m / sz - 1 - x / sz) * sz, sz);
}

void Query8(int sz) {
	for (int x = 0; x < m; x += sz) for (int y = 0; y < m; y += sz)
		F(x, y, (m / sz - 1 - y / sz) * sz, (x / sz) * sz, sz);
}

int main() {
	fastio;
	cin >> n >> q; m = 1 << n;
	for (int i = 0; i < m; i++) for (int j = 0; j < m; j++) cin >> v[i][j];
	while (q--) {
		int a, b; cin >> a >> b; C();
		if (a == 1) Query1(1 << b);
		else if (a == 2) Query2(1 << b);
		else if (a == 3) Query3(1 << b);
		else if (a == 4) Query4(1 << b);
		else if (a == 5) Query5(1 << b);
		else if (a == 6) Query6(1 << b);
		else if (a == 7) Query7(1 << b);
		else if (a == 8) Query8(1 << b);
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) cout << v[i][j] << ' ';
		cout << '\n';
	}
}