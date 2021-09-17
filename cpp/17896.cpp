#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string s; cin >> s;
	regex r0(R"(meow)");
	regex r1(R"((eow|mow|mew|meo)|(me.ow)|(m.ow|me.w)|(moew))");
	regex r2(R"((me|mo|mw|eo|ew|ow)|(m.o|e.w|m..w)|(em.w|m.wo))");
	regex r3(R"(m|e|o|w)");

	auto Sol = [&]() -> int {
		if (regex_search(s, r0)) return 0;
		if (regex_search(s, r1)) return 1;
		if (regex_search(s, r2)) return 2;
		if (regex_search(s, r3)) return 3;
		return 4;
	};
	cout << Sol() << '\n';
}