#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, t1 = 0, t2 = 0; cin >> n;
		string a, b; cin >> a >> b;
		for (int i = 0; i < n; i++)
			if (a[i] != b[i]) (a[i] == 'W' ? t1 : t2)++;
		cout << max(t1, t2) << '\n';
	}
}