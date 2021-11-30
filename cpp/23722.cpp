#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	for (int v[4]; cin >> v[0] >> v[1] >> v[2] >> v[3];) {
		while (1) {
			sort(v, v + 4, greater<>{});
			int i = 0;
			while (i + 1 < 4 && v[i + 1]) i++;
			if (!i) break;
			for (int j = i - 1; j >= 0; j--) v[j] -= v[i];
		}
		if (v[0]) cout << v[0] << '\n';
		else break;
	}
}