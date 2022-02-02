#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, v[100'001];
vector<int> res[100'001];

int main() {
	fastio;
	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		int t; cin >> t;
		res[t].push_back(i);
	}
	for (int i = 1, cur = 1; i <= n; i++) {
		for (auto it = res[i].rbegin(); it != res[i].rend(); it++)
			v[*it] = cur++;
	}
	for (int i = 1; i <= n; i++) cout << v[i] << ' ';
	cout << '\n';
}