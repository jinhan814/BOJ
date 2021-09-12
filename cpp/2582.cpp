#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Random {
	mt19937 rd;
	Random() : rd((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {}
	int GetInt(int l = 0, int r = 32767) {
		return uniform_int_distribution<int>(l, r)(rd);
	}
	double GetDouble(double l = 0, double r = 1) {
		return uniform_real_distribution<double>(l, r)(rd);
	}
} Rand;

struct State {
	vector<int> v; int n;
	State(int n) : v(n), n(n) {}
	void Flip(int i) {
		v[i] ^= (1LL << n) - 1;
	}
	int GetScore() {
		int ret = 0;
		for (int j = 0; j < n; j++) {
			int t = 0;
			for (int i = 0; i < n; i++) if (v[i] & 1 << j) t++;
			ret += min(t, n - t);
		}
		return ret;
	}
};

int SA(State st, double T = 2.5, double d = 0.9999) {
	int n = st.n, ret = st.GetScore();
    for (int i = 0; i < 10'000; i++, T *= d) {
		State nxt = st; nxt.Flip(Rand.GetInt(0, n - 1));
		double p = exp((st.GetScore() - nxt.GetScore()) / T);
		if (p > Rand.GetDouble(0, 1)) st = nxt;
        ret = min(ret, st.GetScore());
	}
	return ret;
}

int main() {
	fastio;
	int n; cin >> n;
	State st(n);
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		for (int j = 0; j < n; j++)
			if (s[j] == 'H') st.v[i] |= 1 << j;
	}
	cout << SA(st) << '\n';
}