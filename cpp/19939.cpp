#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int Sol(int n, int m) {
    if (m * (m + 1) >> 1 > n) return -1;
    n -= m * (m + 1) >> 1;
    return n % m ? m : m - 1;
}

int main() {
    fastio;
    int n, m; cin >> n >> m;
    cout << Sol(n, m) << '\n';
}