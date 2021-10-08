#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int A[1001]{ 1, 1 };

int main() {
	fastio;
	for (int i = 2; i <= 1000; i++) {
		for (int cur = 1; ; cur++) {
			bool flag = 1;
			for (int k = 1; i - 2 * k >= 0; k++)
				if (cur - A[i - k] == A[i - k] - A[i - 2 * k]) flag = 0;
			if (flag) { A[i] = cur; break; }
		}
	}
	int n; cin >> n;
	cout << A[n] << '\n';
}