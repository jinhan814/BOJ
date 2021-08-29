#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

vector<pair<int, int>> Factorize(int n) { //must be n > 1
    vector<pair<int, int>> ret;
    for (int i = 2; i * i <= n; i++) {
        if (n % i) continue;
        int t = 0;
        while (n % i == 0) t++, n /= i;
        ret.push_back({ i, t });
    }
    if (n != 1) ret.push_back({ n, 1 });
    return ret;
}

int Sol(int n) {
    if (n == 1) return 1;
    auto v = Factorize(n);
    if (v.back().first >= 10) return -1;

    int ret = 0, t2 = 0, t3 = 0;
    for (auto& [a, b] : v) {
        if (a == 2) t2 = b;
        else if (a == 3) t3 = b;
        else ret += b;
    }

    if (t3) ret += t3 / 2, t3 %= 2;
    if (t2) ret += t2 / 3, t2 %= 3;
    if (t2 + t3) ret += t2 + t3 + 1 >> 1;
    return ret;
}

int main() {
    fastio;
    int N; cin >> N;
    while (N--) {
        int n; cin >> n;
        cout << Sol(n) << '\n';
    }
}