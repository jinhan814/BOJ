#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, k, cnt = 0; cin >> n >> k;
	string s; cin >> s;
	for (int i = 0; i < n; i++) {
		if (s[i] != 'P') continue;
		for (int j = i - k; j <= i + k; j++) {
			if (0 <= j && j < n && s[j] == 'H') {
				s[j] = 'X', cnt++;
				break;
			}
		}
	}
	cout << cnt << '\n';
}