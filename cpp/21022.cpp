#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
    int n, ans{}; cin >> n; int v[n][2];
    for (int j = 0; j < 2; j++)
        for (int i = 0; i < n; i++)
            cin >> v[i][j];
    for (int i = 0; i < n; i++)
        if (v[i][0] >= v[i][1])
            ans += v[i][0] ^ v[i][1] ? 3 : 1;
	cout << ans;
}