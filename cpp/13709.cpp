#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ull = uint64_t;

ull n, v[100'000];

ull Gauss() {
    int rank = 0;
    for (int j = 59; j >= 0 && rank < n; j--) {
        if (~v[rank] & 1ULL << j) {
            int idx = -1;
            for (int i = rank + 1; i < n; i++) if (v[i] & 1ULL << j) { idx = i; break; }
            if (idx == -1) continue;
            v[rank] ^= v[idx];
        }
        for (int i = 0; i < n; i++) {
            if (rank == i) continue;
            if (v[i] & 1ULL << j) v[i] ^= v[rank];
        }
        rank++;
    }

    ull ret = 0;
    for (int i = 0; i < rank; i++) ret ^= v[i];
    return ret;
}

int main() {
	fastio;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> v[i];
    cout << Gauss() << '\n';
}