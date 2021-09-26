#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
    fastio;
    int N; cin >> N;
    while (N--) {
        int l, n; cin >> l >> n;
        int mn = 0, mx = 0;
        while (n--) {
            int t; cin >> t;
            mn = max(mn, min(t, l - t));
            mx = max(mx, max(t, l - t));
        }
        cout << mn << ' ' << mx << '\n';
    }
}