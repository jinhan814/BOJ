#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
    fastio;
    int n, ans = 0; cin >> n;
    vector<int> v(n);
    for (auto& i : v) cin >> i;
    while (v.size() > 1) {
        auto it = max_element(v.begin(), v.end());
        if (it == v.begin() || next(it) != v.end() && *prev(it) < *next(it))
            ans += *it + *next(it), v.erase(next(it));
        else ans += *it + *prev(it), v.erase(prev(it));
    }
    cout << ans << '\n';
}