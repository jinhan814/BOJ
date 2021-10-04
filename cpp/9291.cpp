#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

inline bool Check(int v[]) {
	for (int i = 0; i < 9; i++) {
		int flag = 0;
		for (int j = 0; j < 9; j++) flag |= 1 << v[i * 9 + j];
		if (flag != 0b1111111110) return 0;
	}
	for (int i = 0; i < 9; i++) {
		int flag = 0;
		for (int j = 0; j < 9; j++) flag |= 1 << v[j * 9 + i];
		if (flag != 0b1111111110) return 0;
	}
	for (int x = 0; x < 9; x += 3) for (int y = 0; y < 9; y += 3) {
		int flag = 0;
		for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) flag |= 1 << v[(x + i) * 9 + (y + j)];
		if (flag != 0b1111111110) return 0;
	}
	return 1;
}

int main() {
	fastio;
	int N, v[81]; cin >> N;
	for (int c = 1; c <= N; c++) {
		for (int i = 0; i < 81; i++) cin >> v[i];
		cout << "Case " << c << ": ";
		cout << (Check(v) ? "CORRECT" : "INCORRECT") << '\n';
	}
}