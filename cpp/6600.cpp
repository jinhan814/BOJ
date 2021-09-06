#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

const double PI = acos(-1);

int main() {
	fastio;
	cout << fixed << setprecision(2);
	for (double x1, y1, x2, y2, x3, y3; cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;) {
		double d = hypot(x3 - x2, y3 - y2);
		double ax = x2 - x1, ay = y2 - y1, bx = x3 - x1, by = y3 - y1;
		double theta = acos((ax * bx + ay * by) / hypot(ax, ay) / hypot(bx, by));
		cout << d / sin(theta) * PI << '\n';
	}
}