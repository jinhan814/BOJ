#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
    fastio;
    int n, ans = 0; cin >> n;
    for (; n; n /= 10) {
        int t = 1;
        for (int i = 0; i < 5; i++) t *= n % 10;
        ans += t;
    }
    cout << ans << '\n';
}