#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	for (string a, b; cin >> a >> b && a != "#";) {
		const int n = a.size(); int t1{}, t2{}, t3{}; auto t = b;
		for (int i = 0; i < n; i++) if (a[i] == b[i]) t1++, a[i] = b[i] = '_';
		for (int i = 0; i < n; i++) if (a[i] != '_')
			if (i && a[i] == b[i - 1]) t2++, a[i] = b[i - 1] = '_';
			else if (i + 1 < n && a[i] == b[i + 1]) t2++, a[i] = b[i + 1] = '_';
		for (int i = 0; i < n; i++) if (a[i] != '_')
			for (int j = 0; j < n; j++) if (a[i] == b[j]) { t3++, a[i] = b[j] = '_'; break; }
		cout << t << ": " << t1 << " black, " << t2 << " grey, " << t3 << " white" << '\n';
	}
}