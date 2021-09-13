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

int GetScore(vector<int> v, int64_t st) {
	int n = v.size();
	for (int l = 0, r = n - 1; l < r; l++, r--) {
		while (l < r && ~st & 1LL << l) l++;
		while (l < r && ~st & 1LL << r) r--;
		if (l < r) swap(v[l], v[r]);
	}
	vector<int> LIS;
	for (int i = 0; i < n; i++) {
		if (LIS.empty() || LIS.back() <= v[i]) LIS.push_back(v[i]);
		else *lower_bound(LIS.begin(), LIS.end(), v[i]) = v[i];
	}
	return LIS.size();
}

int SA(const vector<int>& v, double T = 10.0, double d = 0.9999) {
	int n = v.size(), ret = 1, score = 1; int64_t st = 0;
    for (int i = 0; i < 100'000; i++, T *= d) {
		auto nxt = st ^ 1LL << Rand.GetInt(0, n - 1);
		auto nxt_score = GetScore(v, nxt);
		double p = exp(-(score - nxt_score) / T);
		if (p > Rand.GetDouble(0, 1)) st = nxt, score = nxt_score;
		ret = max(ret, score);
	}
	return ret;
}

int main() {
	fastio;
	int n, ans = 1; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 0; i < 5; i++) ans = max(ans, SA(v));
    cout << ans << '\n';
}