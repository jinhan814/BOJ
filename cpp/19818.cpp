#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define all(v) (v).begin(), (v).end()
using ri = sregex_iterator;

vector<string> ParseCite(const string& s) {
	vector<string> ret;
	regex r(R"(\{(.+?)\})");
	for (auto it = ri(all(s), r); it != ri(); it++)
		ret.push_back(it->str());
	return ret;
}

string ParseName(const string& s) {
	regex r(R"(\{(.+?)\})");
	return ri(all(s), r)->str();
}

int main() {
	fastio;
	bool flag = 0;
	vector<string> cite;
	vector<pair<string, string>> bibitem;
	map<string, string> M;

	for (string s; getline(cin, s);) {
		if (s.substr(0, 6) == "\\begin") flag = 1;
		else if (s.substr(0, 4) == "\\end") break;
		else if (flag) {
			string name = ParseName(s);
			bibitem.push_back({ name, s }), M[name] = s;
		}
		else for (const auto& i : ParseCite(s)) cite.push_back(i);
	}

	bool IsValid = 1;
	for (int i = 0; i < cite.size(); i++) {
		if (cite[i] != bibitem[i].first) IsValid = 0;
	}

	if (IsValid) cout << "Correct" << '\n';
	else {
		cout << "Incorrect" << '\n';
		cout << R"(\begin{thebibliography}{99})" << '\n';
		for (const auto& i : cite) cout << M[i] << '\n';
		cout << R"(\end{thebibliography})" << '\n';
	}
}