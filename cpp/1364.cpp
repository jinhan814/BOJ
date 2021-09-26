#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

ll Sol(ll n) {
    ll ret = (n / 6) * (n / 6 + 1) * 3 + 1;
    if (n % 6) ret += (n / 6) + (n / 6 + 1) * (n % 6 - 1);
    return ret;
}

int main() {
	fastio;
	int n; cin >> n;
    cout << Sol(n) << '\n';
}