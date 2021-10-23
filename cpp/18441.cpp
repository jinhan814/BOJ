#define private public
#include <bitset>
#undef private

#include <bits/stdc++.h>
#include <x86intrin.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

// reference : https://gist.github.com/cgiosy/a441de545c9e96b1d7b02cc7a00561f9?fbclid=IwAR0N3Woe8GwzAsxMapbEE9b7rrE_XArl50BRdQ9ZOTCxk-2X5BRrm-HBVpo
template<size_t _Nw> void _M_do_sub(_Base_bitset<_Nw>& A, const _Base_bitset<_Nw>& B) {
	for (int i = 0, c = 0; i < _Nw; i++) c = _subborrow_u64(c, A._M_w[i], B._M_w[i], (unsigned long long*) & A._M_w[i]);
}
template<> void _M_do_sub(_Base_bitset<1>& A, const _Base_bitset<1>& B) { A._M_w -= B._M_w; }
template<size_t _Nb> bitset<_Nb>& operator-=(bitset<_Nb>& A, const bitset<_Nb>& B) { return _M_do_sub(A, B), A; }
template<size_t _Nb> inline bitset<_Nb> operator-(const bitset<_Nb>& A, const bitset<_Nb>& B) { bitset<_Nb> C(A); return C -= B; }

template<size_t sz>
string _LCS(const string& a, const string& b) {
    bitset<sz> x, S[26];
	vector<bitset<sz>> D(a.size() + 1);
    for (int i = 0; i < b.size(); i++) S[b[i] - 'a'][i] = 1;
    for (int i = 0; i < a.size(); i++) {
        x = S[a[i] - 'a'] | D[i];
		D[i + 1] = D[i] << 1, D[i + 1][0] = 1;
		D[i + 1] = x & (x ^ (x - D[i + 1]));
    }
	string ret;
	for (int x = a.size(), y = b.size() - 1; x > 0; x--) {
		while (y >= 0 && !D[x][y]) y--;
		if (y < 0) break;
		while (x > 0 && D[x - 1][y]) x--;
		ret.push_back(b[y--]);
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

string LCS(const string& a, const string& b) {
	if (b.size() <= 64) return _LCS<64>(a, b);
	if (b.size() <= 128) return _LCS<128>(a, b);
	if (b.size() <= 192) return _LCS<192>(a, b);
	if (b.size() <= 256) return _LCS<256>(a, b);
	if (b.size() <= 320) return _LCS<320>(a, b);
	if (b.size() <= 384) return _LCS<384>(a, b);
	if (b.size() <= 448) return _LCS<448>(a, b);
	if (b.size() <= 512) return _LCS<512>(a, b);
	if (b.size() <= 576) return _LCS<576>(a, b);
	if (b.size() <= 640) return _LCS<640>(a, b);
	if (b.size() <= 704) return _LCS<704>(a, b);
	if (b.size() <= 768) return _LCS<768>(a, b);
	if (b.size() <= 832) return _LCS<832>(a, b);
	if (b.size() <= 896) return _LCS<896>(a, b);
	if (b.size() <= 960) return _LCS<960>(a, b);
	if (b.size() <= 1024) return _LCS<1024>(a, b);
	if (b.size() <= 1088) return _LCS<1088>(a, b);
	if (b.size() <= 1152) return _LCS<1152>(a, b);
	if (b.size() <= 1216) return _LCS<1216>(a, b);
	if (b.size() <= 1280) return _LCS<1280>(a, b);
	if (b.size() <= 1344) return _LCS<1344>(a, b);
	if (b.size() <= 1408) return _LCS<1408>(a, b);
	if (b.size() <= 1472) return _LCS<1472>(a, b);
	return _LCS<1536>(a, b);
}

int main() {
	fastio;
	int N; cin >> N;
	for (int c = 1; c <= N; c++) {
		string s, mx; cin >> s;
		for (int i = 1; i < s.size(); i++) {
			auto a = s.substr(0, i);
			auto b = s.substr(i, s.size());
			auto res = a.size() < b.size() ? LCS(b, a) : LCS(a, b);
			if (mx.size() < res.size()) mx = res;
		}
		cout << "Case #" << c << ": " << 2 * mx.size() << '\n';
		if (mx.size()) cout << mx << mx << '\n';
	}
}