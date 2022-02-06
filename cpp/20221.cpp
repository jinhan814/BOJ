#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

vector<string> Sol(const vector<string>& v) {
	vector<string> ret;
	for (const auto& i : v) {
		string prv = ret.size() ? ret.back() : "0";
		string cur = i;
		if (prv.size() > cur.size()) return {};
		prv = string(cur.size() - prv.size(), '0') + prv;
		auto DFS = [&](int i, auto&& DFS) -> string {
			if (i == cur.size()) return "";
			if (cur[i] != '6' && cur[i] != '9') {
				if (cur[i] < prv[i]) return "-";
				if (cur[i] > prv[i]) {
					auto res = cur.substr(i);
					for (auto& i : res) if (i == '9') i = '6';
					return res;
				}
				auto res = DFS(i + 1, DFS);
				if (res == "-") return res;
				return string(1, cur[i]) + res;
			}
			else {
				if (prv[i] < '6') {
					auto res = cur.substr(i + 1);
					for (auto& i : res) if (i == '9') i = '6';
					return string(1, '6') + res;
				}
				if (prv[i] != '6' && prv[i] < '9') {
					auto res = cur.substr(i + 1);
					for (auto& i : res) if (i == '9') i = '6';
					return string(1, '9') + res;
				}
				auto res = DFS(i + 1, DFS);
				if (res == "-") {
					if (prv[i] != '6') return res;
					res = cur.substr(i + 1);
					for (auto& i : res) if (i == '9') i = '6';
					return string(1, '9') + res;
				}
				return string(1, prv[i]) + res;
			}
		};
		auto res = DFS(0, DFS);
		if (res == "-") return {};
		ret.push_back(res);
	}
	return ret;
}

void Print(const vector<string>& v) {
	if (v.size()) {
		cout << "possible" << '\n';
		for (const auto& i : v) cout << i << '\n';
	}
	else cout << "impossible" << '\n';
}

int main() {
	fastio;
	int n; cin >> n;
	vector<string> v(n);
	for (auto& i : v) cin >> i;
	Print(Sol(v));
}