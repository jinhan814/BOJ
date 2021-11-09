#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string s, v[51][2]; cin >> s;
	for (int i = 0; i < s.size(); i++) {
		{
			string t1 = v[i][0] + s[i], t2 = v[i][1] + s[i];
			reverse(t2.begin(), t2.end());
			v[i + 1][0] = min(t1, t2);
		} {
			string t1 = v[i][1] + s[i], t2 = v[i][0] + s[i];
			reverse(t1.begin(), t1.end());
			v[i + 1][1] = min(t1, t2);
			reverse(v[i + 1][1].begin(), v[i + 1][1].end());
		}
	}
	reverse(v[s.size()][1].begin(), v[s.size()][1].end());
	cout << min(v[s.size()][0], v[s.size()][1]) << '\n';
}