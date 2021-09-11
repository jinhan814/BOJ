#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	for (int c = 1; c <= N; c++) {
		int n; string s; cin >> n >> s;
		cout << "Case #" << c << ": ";
		for (int i = 0; i < n; i++) {
			int cnt = 1;
			for (int j = i - 1; j >= 0 && s[j] < s[j + 1]; j--) cnt++;
			cout << cnt << ' ';
		}
		cout << '\n';
	}
}