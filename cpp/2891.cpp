#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
    fastio;
    int n, m, k, v[10]{}, w[10]{}; cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int t; cin >> t; --t;
        v[t] = 1;
    }
    for (int i = 0; i < k; i++) {
        int t; cin >> t; --t;
        if (v[t]) v[t] = 0;
        else w[t] = 1;
    }
    for (int i = 0; i < n; i++) {
        if (!w[i]) continue;
        if (i && v[i - 1]) v[i - 1] = 0;
        else if (i + 1 < n && v[i + 1]) v[i + 1] = 0;
    }
    cout << reduce(v, v + n) << '\n';
}