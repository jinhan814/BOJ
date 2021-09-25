#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define double long double
const double PI = acos(-1);

int main() {
	fastio;
	cout << fixed << setprecision(3);
	for (double D, V; cin >> D >> V && D;) {
		const double val = D * D * D - V * 6 / PI;
		cout << cbrt(val) << '\n';
	}
}