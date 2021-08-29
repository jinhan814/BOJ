#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
    fastio;
    int N; cin >> N;
    while (N--) {
        int n, k; cin >> n >> k; k = min(k, n);
        cout << (2 * n - k) * (k + 1) * 2 << '\n';
    }
}