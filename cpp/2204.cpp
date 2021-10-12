#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	for (int n; cin >> n && n;) {
		vector<string> v(n);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << *min_element(v.begin(), v.end(), [](const string& a, const string& b) {
			const int sz = min(a.size(), b.size());
			for (int i = 0; i < sz; i++)
				if ((a[i] | 32) ^ (b[i] | 32))
					return (a[i] | 32) < (b[i] | 32);
			return a.size() < b.size();
		}) << '\n';
	}
}