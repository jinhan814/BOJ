#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t
using pii = pair<int, int>;

int GetDist(const pii& a, const pii& b) {
    return (a.first - b.first) * (a.first - b.first)
        + (a.second - b.second) * (a.second - b.second);
}

bool Sol(pii v[]) {
    map<int, int> M;
    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 4; j++)
            M[GetDist(v[i], v[j])]++;
    if (M.size() != 2) return 0;
    if (M.begin()->second != 4) return 0;
    if (M.begin()->first << 1 != prev(M.end())->first) return 0;
    return 1;
}

int32_t main() {
    fastio;
    int N; cin >> N;
    while (N--) {
        pii v[4];
        for (int i = 0; i < 4; i++) cin >> v[i].first >> v[i].second;
        cout << Sol(v) << '\n';
    }
}