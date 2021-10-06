#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string s, t, rt; cin >> t >> s; rt = t; reverse(rt.begin(), rt.end());
	string S1, S2;
	deque<char> DQ(s.begin(), s.end());

	auto QueryL = [&]() -> bool {
		while ((S1.size() < t.size() || S1.substr(S1.size() - t.size(), t.size()) != t) && DQ.size())
			S1.push_back(DQ.front()), DQ.pop_front();
		for (int i = 0; (S1.size() < t.size() || S1.substr(S1.size() - t.size(), t.size()) != t) && S2.size() && i < t.size(); i++)
			S1.push_back(S2.back()), S2.pop_back();
		if (S1.size() >= t.size() && S1.substr(S1.size() - t.size(), t.size()) == t) {
			for (int i = t.size(); i-- > 0;) S1.pop_back();
			return 1;
		}
		return 0;
	};

	auto QueryR = [&]() -> bool {
		while ((S2.size() < rt.size() || S2.substr(S2.size() - rt.size(), rt.size()) != rt) && DQ.size())
			S2.push_back(DQ.back()), DQ.pop_back();
		for (int i = 0; (S2.size() < rt.size() || S2.substr(S2.size() - rt.size(), rt.size()) != rt) && S1.size() && i < rt.size(); i++)
			S2.push_back(S1.back()), S1.pop_back();
		if (S2.size() >= rt.size() && S2.substr(S2.size() - rt.size(), rt.size()) == rt) {
			for (int i = rt.size(); i-- > 0;) S2.pop_back();
			return 1;
		}
		return 0;
	};

	int q, cnt = 0; cin >> q;
	for (char c; q-- && cin >> c;) cnt += c == 'L' ? QueryL() : QueryR();

	auto GetRes = [&]() -> string {
		string t = S2; reverse(t.begin(), t.end());
		return S1 + string(DQ.begin(), DQ.end()) + t;
	};

	auto Check = [&](const string& s) -> bool { // use KMP if tle
		return s.find(t) == string::npos;
	};

	auto res = GetRes();
	cout << cnt << '\n';
	cout << res << '\n';
	cout << (Check(res) ? "Perfect!" : "You Lose!") << '\n';
}