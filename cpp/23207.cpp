#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int c = 1;
	for (string a, b; cin >> a >> b; c++) {
		cout << "Case " << c << ": ";
		if (a.size() == 1) cout << "UNIQUE" << '\n';
		else if (a[1] == '#') cout << (a[0] == 'G' ? 'A' : char(a[0] + 1)) << "b " << b << '\n';
		else cout << (a[0] == 'A' ? 'G' : char(a[0] - 1)) << "# " << b << '\n';
	}
}