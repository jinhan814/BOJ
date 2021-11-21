#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

using vi = vector<int>;
using vvi = vector<vi>;

int Calc(const vvi& v) {
    const int t1 = v[0][0] * (v[1][1] * v[2][2] - v[2][1] * v[1][2]);
    const int t2 = v[1][0] * (v[2][1] * v[0][2] - v[0][1] * v[2][2]);
    const int t3 = v[2][0] * (v[0][1] * v[1][2] - v[1][1] * v[0][2]);
    return t1 + t2 + t3;
}

string Conv(double val) {
    if (-0.0005 < val && val < 0.0005) return "0.000";
    if (val < 0) return "-" + Conv(-val);
    stringstream out; out << fixed << setprecision(3) << val;
    return out.str();
}

int32_t main() {
    fastio;
    int N; cin >> N;
    while (N--) {
        vvi v(3, vi(4)), t(3, vi(3));
        for (int i = 0; i < 3; i++) for (int j = 0; j < 4; j++) cin >> v[i][j];
        for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) t[i][j] = v[i][j];

        int Det = Calc(t), res[3];
        for (int k = 0; k < 3; k++) {
            for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) t[i][j] = v[i][j];
            for (int i = 0; i < 3; i++) t[i][k] = v[i][3];
            res[k] = Calc(t);
        }

        cout << res[0] << ' ' << res[1] << ' ' << res[2] << ' ' << Det << '\n';
        if (Det == 0) cout << "No unique solution" << '\n';
        else {
            cout << "Unique solution: ";
            cout << Conv(1. * res[0] / Det) << ' ';
            cout << Conv(1. * res[1] / Det) << ' ';
            cout << Conv(1. * res[2] / Det) << '\n';
        }
        cout << '\n';
    }
}