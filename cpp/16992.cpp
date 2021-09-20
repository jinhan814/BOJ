#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

/* reference : https://blog.naver.com/jhnah917/222511192769 */

struct Random {
	mt19937 rd;
	Random(int seed) : rd(seed) {}
	template<typename T = int>
	T GetInt(T l = 0, T r = 32767) {
		return uniform_int_distribution<T>(l, r)(rd);
	}
	double GetDouble(double l = 0, double r = 1) {
		return uniform_real_distribution<double>(l, r)(rd);
	}
};

struct CNF {
	using tii = tuple<char, char, char>;
	vector<tii> v; int m;
	CNF(int m) : v(m), m(m) {}
};

struct State {
	bitset<101> v; int n;
	State(int n) : n(n) {}
	void Flip(Random& Rand) {
		v[Rand.GetInt(1, n)].flip();
	}
    void Flip(Random& Rand, const CNF& c) {
        int rnd = Rand.GetInt(0, 2), idx = Check(c);
        if (rnd == 0) v[abs(get<0>(c.v[idx]))].flip();
        else if (rnd == 1) v[abs(get<1>(c.v[idx]))].flip();
        else if (rnd == 2) v[abs(get<2>(c.v[idx]))].flip();
    }
	int GetScore(const CNF& c) const {
		int ret = c.m;
		for (const auto& [a, b, c] : c.v) {
			ret -= (a > 0 ? v[a] : !v[-a])
				|| (b > 0 ? v[b] : !v[-b])
				|| (c > 0 ? v[c] : !v[-c]);
		}
		return ret;
	}
    int Check(const CNF& cnf) {
        for (int i = 0; i < cnf.m; i++) {
            const auto& [a, b, c] = cnf.v[i];
            if (a > 0 ? v[a] : !v[-a]) continue;
            if (b > 0 ? v[b] : !v[-b]) continue;
            if (c > 0 ? v[c] : !v[-c]) continue;
            return i;
        }
        return -1;
    }
};

State SA(State st, const CNF& c, int seed, bool flag = 0, double T = 1.5, double d = 0.9999) {
    Random Rand(seed); State ret = st;
    int score = st.GetScore(c), ret_score = score;
	for (int i = 0; i < 30'000; i++, T *= d) {
		auto nxt = st; flag ? nxt.Flip(Rand, c) : nxt.Flip(Rand);
		int nxt_score = nxt.GetScore(c);
		double p = exp((score - nxt_score) / T);
		if (p > Rand.GetDouble(0, 1)) st = nxt, score = nxt_score;
		if (ret_score > score) ret_score = score, ret = st;
        if (ret_score == 0) return ret;
	}
	return ret;
}

int main() {
	fastio;
	int n, m; cin >> n >> m;
	State st(n); CNF c(m);
	for (auto& [a, b, c] : c.v) {
		int t1, t2, t3; cin >> t1 >> t2 >> t3;
		a = t1, b = t2, c = t3;
    }

    auto Print = [&](const State& st) {
        cout << 1 << '\n';
        for (int i = 1; i <= n; i++) cout << st.v[i] << ' ';
        cout << '\n'; exit(0);
    };

    if (auto ans = SA(st, c, 0x131072); !ans.GetScore(c)) Print(ans);
    if (auto ans = SA(st, c, 0x265328); !ans.GetScore(c)) Print(ans);
    if (auto ans = SA(st, c, 0x731161); !ans.GetScore(c)) Print(ans);
    if (auto ans = SA(st, c, 0x987654); !ans.GetScore(c)) Print(ans);
    if (auto ans = SA(st, c, 0x314159, 1); !ans.GetScore(c)) Print(ans);
    if (auto ans = SA(st, c, 0x265358, 1); !ans.GetScore(c)) Print(ans);
    if (auto ans = SA(st, c, 0x979323, 1); !ans.GetScore(c)) Print(ans);
    if (auto ans = SA(st, c, 0x846264, 1); !ans.GetScore(c)) Print(ans);
    if (auto ans = SA(st, c, 0x338327, 1); !ans.GetScore(c)) Print(ans);
	cout << 0 << '\n';
}