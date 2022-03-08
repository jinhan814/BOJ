#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

using i64 = long long;

i64 v[100'000]; string s;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		memset(v, 0, sizeof v);
		cin >> s;
		for (int i = 0, t = 0; i < s.size(); i++) {
			if (s[i] == '(' && s[i + 1] == ')') v[t >> 5] += i64(1) << (t & 31), i++;
			else if (s[i] == '(') t++;
			else t--;
		}
		cin >> s;
		for (int i = 0, t = 0; i < s.size(); i++) {
			if (s[i] == '(' && s[i + 1] == ')') v[t >> 5] -= i64(1) << (t & 31), i++;
			else if (s[i] == '(') t++;
			else t--;
		}
		for (int i = 0; i < 99'999; i++) {
			v[i + 1] += v[i] >> 32;
			v[i] &= (i64(1) << 32) - 1;
		}
		int res = 0;
		for (int i = 100'000; i-- > 0;) {
			if (v[i] > 0) { res = 1; break; }
			if (v[i] < 0) { res = 2; break; }
		}
		cout << "=><"[res] << '\n';
	}
}