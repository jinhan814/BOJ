#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int M1 = 29, M2 = 34483;
using pii = pair<int, int>;
using poly = vector<int>;

template<int MOD>
int Pow(int x, int n) {
    int ret = 1;
    for (; n; n >>= 1) {
        if (n & 1) ret = ret * x % MOD;
        x = x * x % MOD;
    }
    return ret;
}

int minv(int a, int b) {
    if (a == 0 && b == 1) return 0;
    if (a == 1) return 1;
    return b - minv(b % a, a) * b / a;
}

pii crt(pii A, pii B) {
    if (A.second == -1 || B.second == -1) return { -1, -1 };
    if (A.second == 1) return B;
    if (B.second == 1) return A;
    int g = gcd(A.second, B.second), l = A.second * (B.second / g);
    if ((B.first - A.first) % g != 0) return { -1, -1 };
    int a = A.second / g, b = B.second / g;
    int mul = (B.first - A.first) / g;
    mul = (mul * minv(a % b, b)) % b;
    int ret = (mul * A.second + A.first);
    ret %= l; ret = (ret + l) % l;
    return { ret, l };
}

template<int MOD>
poly BerlekampMassey(const poly& v) {
    poly ls, ret; int lf, ld;
    for (int i = 0, t = 0; i < v.size(); i++, t = 0) {
        for (int j = 0; j < ret.size(); j++) t = (t + 1ll * v[i - j - 1] * ret[j]) % MOD;
        if ((t - v[i]) % MOD == 0) continue;
        if (ret.empty()) { ret.resize(i + 1), lf = i, ld = (t - v[i]) % MOD; continue; }
        const int k = -(v[i] - t) * Pow<MOD>(ld, MOD - 2) % MOD;
        poly cur(i - lf - 1); cur.push_back(k);
        for (const auto& j : ls) cur.push_back(-j * k % MOD);
        if (cur.size() < ret.size()) cur.resize(ret.size());
        for (int j = 0; j < ret.size(); j++) cur[j] = (cur[j] + ret[j]) % MOD;
        if (i - lf + (int)ls.size() >= (int)ret.size()) ls = ret, lf = i, ld = (t - v[i]) % MOD;
        ret = cur;
    }
    for (auto& i : ret) i = (i % MOD + MOD) % MOD;
    reverse(ret.begin(), ret.end());
    return ret;
}

template<int MOD>
struct Kitamasa {
    static int Mod(int x) {
        x %= MOD;
        return x < 0 ? x + MOD : x;
    }
    static poly Mul(const poly& a, const poly& b) {
        poly ret(a.size() + b.size() - 1);
        for (int i = 0; i < a.size(); i++) for (int j = 0; j < b.size(); j++) {
            ret[i + j] = (ret[i + j] + a[i] * b[j]) % MOD;
        }
        return ret;
    }
    static poly Div(const poly& a, const poly& b) {
        poly ret(a.begin(), a.end());
        for (int i = ret.size() - 1; i >= b.size() - 1; i--) for (int j = 0; j < b.size(); j++) {
            ret[i + j - b.size() + 1] = Mod(ret[i + j - b.size() + 1] - ret[i] * b[j]);
        }
        ret.resize(b.size() - 1);
        return ret;
    }
    static int Calc(poly rec, poly dp, int n) {
        if (dp.size() > rec.size()) dp.resize(rec.size());
        poly d = { 1 }, xn = { 0, 1 };
        poly f(rec.size() + 1); f.back() = 1;
        for (int i = 0; i < rec.size(); i++) f[i] = Mod(-rec[i]);
        while (n) {
            if (n & 1) d = Div(Mul(d, xn), f);
            n >>= 1; xn = Div(Mul(xn, xn), f);
        }
        int ret = 0;
        for (int i = 0; i < dp.size(); i++) ret = Mod(ret + dp[i] * d[i]);
        return ret;
    }
};

constexpr int L = 200; // limit
int n, m, DP1[L][24][24], DP2[L][24][24];

void Calc(int n) {
    memset(DP1, 0, sizeof DP1), memset(DP2, 0, sizeof DP2); DP1[0][0][0] = DP2[0][0][0] = 1;
    for (int d = 1; d < L; d++) {
        for (int i = 0; i < n << 1; i++) for (int j = 0; j < n << 1; j++) {
            for (int k = 0; k < 8; k++) {
                int nx = i + "10013443"[k] - '2';
                int ny = j + "43100134"[k] - '2';
                if (nx < 0 || nx >= n << 1 || ny < 0 || ny >= n << 1) continue;
                (DP1[d][nx][ny] += DP1[d - 1][i][j]) %= M1;
                (DP2[d][nx][ny] += DP2[d - 1][i][j]) %= M2;
            }
        }
    }
}

int main() {
	fastio;
    int N; cin >> N;
    while (N--) {
        cin >> n >> m; Calc(n);
        poly v1, v2;
        for (int i = 0; i < L; i++) {
            int t1 = i ? v1.back() : 0, t2 = i ? v2.back() : 0;
            t1 += DP1[i][0][0] + DP1[i][2 * n - 1][0] + DP1[i][0][2 * n - 1] + DP1[i][2 * n - 1][2 * n - 1];
            t2 += DP2[i][0][0] + DP2[i][2 * n - 1][0] + DP2[i][0][2 * n - 1] + DP2[i][2 * n - 1][2 * n - 1];
            v1.push_back(t1 % M1), v2.push_back(t2 % M2);
        }
        poly rec1 = BerlekampMassey<M1>(v1);
        poly rec2 = BerlekampMassey<M2>(v2);
        auto res1 = Kitamasa<M1>::Calc(rec1, v1, m);
        auto res2 = Kitamasa<M2>::Calc(rec2, v2, m);
        auto [res, _] = crt({ res1, M1 }, { res2, M2 });
        cout << res << '\n';
    }
}