#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, q, v[128][128], t[128][128];

inline void C() { for (int i = 0; i < m; i++) memcpy(t[i], v[i], m << 2); }
inline void F(int x1, int y1, int x2, int y2, int sz) {
	for (int i = 0; i < sz; i++) for (int j = 0; j < sz; j++)
		v[x2 + i][y2 + j] = t[x1 + i][y1 + j];
}

void Query(int cmd, int sz) {
	for (int x = 0; x < m; x += sz) for (int y = 0; y < m; y += sz)
		if (cmd <= 4) for (int i = 0; i < sz; i++) for (int j = 0; j < sz; j++) {
			if (cmd == 1) v[x + i][y + j] = t[x + (sz - 1 - i)][y + j];
            else if (cmd == 2) v[x + i][y + j] = t[x + i][y + (sz - 1 - j)];
            else if (cmd == 3) v[x + i][y + j] = t[x + (sz - 1 - j)][y + i];
            else v[x + i][y + j] = t[x + j][y + (sz - 1 - i)];
        }
        else if (cmd == 5) F(x, y, m - sz - x, y, sz);
        else if (cmd == 6) F(x, y, x, m - sz - y, sz);
        else if (cmd == 7) F(x, y, (y / sz) * sz, (m / sz - 1 - x / sz) * sz, sz);
        else F(x, y, (m / sz - 1 - y / sz) * sz, (x / sz) * sz, sz);
}

int main() {
	fastio;
	cin >> n >> q; m = 1 << n;
	for (int i = 0; i < m; i++) for (int j = 0; j < m; j++) cin >> v[i][j];
    for (int a, b; q-- && cin >> a >> b; C(), Query(a, 1 << b));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) cout << v[i][j] << ' ';
		cout << '\n';
	}
}