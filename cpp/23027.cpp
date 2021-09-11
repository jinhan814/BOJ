#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string s; cin >> s; bool t[3]{};
	for (const auto& i : s) if (i - 'A' < 3) t[i - 'A'] = 1;
	if (t[0]) { for (auto& i : s) if (string("BCDF").find(i) != -1) i = 'A'; }
	else if (!t[0] && t[1]) { for (auto& i : s) if (string("CDF").find(i) != -1) i = 'B'; }
	else if (!t[0] && !t[1] && t[2]) { for (auto& i : s) if (string("DF").find(i) != -1) i = 'C'; }
	else if (!t[0] && !t[1] && !t[2]) s = string(s.size(), 'A');
	cout << s << '\n';
}