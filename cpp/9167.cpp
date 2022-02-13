#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

/* Helper Function */

string Normalize(const string& s) {
	string ret; int cnt = 0;
	for (int i = 0; i < s.size();) {
		while (i < s.size() && s[i] == ' ') i++;
		if (i == s.size()) break;
		while (i < s.size() && s[i] != ' ') ret.push_back(s[i++]);
		ret.push_back(' ');
	}
	return ret;
}

int GetCnt(const string& s) {
	int ret = 0;
	for (int i = 0; i < s.size(); i++) {
		bool flag = 0;
		while (i < s.size() && s[i] != ' ') flag |= isalpha(s[i++]);
		ret += flag;
	}
	return (ret + 2) / 3;
}

bool CheckHoly(const string& s) {
	static string DB = "theholygrail";
	for (int i = 0, j = 0; i < s.size(); i++)
		if (s[i] == DB[j] && ++j == 12) return 1;
	return 0;
}

/* BNF */

struct DB {
	vector<string> v; int cnt = 0;
	DB(vector<string> v) : v(v) {}
	string operator() () { return v[cnt++ % v.size()]; }
};

DB PresentPerson({ "steed", "king", "first-born" });
DB PastPerson({ "mother", "father", "grandmother", "grandfather", "godfather" });
DB Noun({ "hamster", "coconut", "duck", "herring", "newt", "peril", "chicken", "vole", "parrot", "mouse", "twit" });
DB PresentVerb({ "is", "masquerades as" });
DB PastVerb({ "was", "personified" });
DB Adjective({ "silly", "wicked", "sordid", "naughty", "repulsive", "malodorous", "ill-tempered" });
DB Adverb({ "conspicuously", "categorically", "positively", "cruelly", "incontrovertibly" });

string PresentRel() { return "your " + PresentPerson() + " " + PresentVerb(); }

string PastRel() { return "your " + PastPerson() + " " + PastVerb(); }

string Modifier() {
	static int cnt = 0; ++cnt;
	if (cnt & 1) return Adjective();
	auto res = Adverb();
	return res + " " + Adjective();
}

string ModifiedNoun() {
	static int cnt = 0; ++cnt;
	if (cnt & 1) return Noun();
	return Modifier() + " " + Noun();
}

string Sentence() {
	static int cnt = -1; cnt = ++cnt % 3;
	if (cnt == 0) return PastRel() + " a " + ModifiedNoun();
	if (cnt == 1) return PresentRel() + " a " + ModifiedNoun();
	return PastRel() + " a " + Noun();
}

string Taunt() {
	static int cnt = -1; cnt = ++cnt % 4;
	if (cnt == 1) {
		auto res1 = Taunt(), res2 = Sentence();
		res2[0] = toupper(res2[0]);
		return res1 + " " + res2;
	}
	if (cnt == 2) {
		auto res = Noun() + "!";
		res[0] = toupper(res[0]);
		return res;
	}
	auto res = Sentence();
	res[0] = toupper(res[0]);
	return res;
}

/* Main Function */

int main() {
	fastio;
	int TauntCnt = -1;
	for (string s; getline(cin, s);) {
		s = Normalize(s); cout << "Knight: " << s << '\n';
		auto cnt = GetCnt(s);
		if (CheckHoly(s)) {
			cnt--;
			cout << "Taunter: (A childish hand gesture). " << '\n';
		}
		while (cnt > 0) {
			cnt -= ++TauntCnt % 3 & 1 ? 2 : 1;
			cout << "Taunter: " << Taunt() << ". \n";
		}
		cout << '\n';
	}
}