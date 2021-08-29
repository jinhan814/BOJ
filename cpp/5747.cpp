#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
    fastio;
    for (int n; cin >> n && n;) {
        int t, t1{}, t2{};
        for (int i = 0; i < n; i++) cin >> t, t1 += t & 1;
        for (int i = 0; i < n; i++) cin >> t, t2 += ~t & 1;
        cout << n - min(t1, t2) - min(n - t1, n - t2) << '\n';
    }
}