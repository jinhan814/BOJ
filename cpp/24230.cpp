#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
    int n, res = 1; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b; --a, --b;
        if (v[a] != v[b]) res++;
    }
    cout << res - !v[0] << '\n';
}