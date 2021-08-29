#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
    fastio;
    int n, m, k; cin >> n >> m >> k;

    vector<vector<double>> v(n + 1);
    while (m--) {
        for (int i = 0; i < n; i++) {
            int a; double b; cin >> a >> b;
            v[a].push_back(b);
        }
    }

    vector<double> w;
    for (int i = 1; i <= n; i++) {
        w.push_back(*max_element(v[i].begin(), v[i].end()));
    }
    sort(w.rbegin(), w.rend());

    double ans = 0;
    for (int i = 0; i < k; i++) ans += w[i];
    cout << fixed << setprecision(1) << ans << '\n';
}