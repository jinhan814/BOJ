#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Converter {
private:
	int DB[10] = {
		0b00111111, 0b00001010, 0b01011101, 0b01001111, 0b01101010,
		0b01100111, 0b01110111, 0b00001011, 0b01111111, 0b01101011,
	};
	string Conv1[10];
	map<string, int> Conv2;
public:
	Converter() {
		for (int i = 0; i < 10; i++) {
			Conv1[i] = to_string(DB[i]);
			while (Conv1[i].size() < 3) Conv1[i].insert(Conv1[i].begin(), '0');
			Conv2[Conv1[i]] = i;
		}
	}
	int operator() (const string& s) {
		int ret = 0;
		for (int i = 0; i < s.size(); i += 3)
			ret = 10 * ret + Conv2[s.substr(i, 3)];
		return ret;
	}
	string operator() (int n) {
		string ret;
		for (; n; n /= 10) ret = Conv1[n % 10] + ret;
		return ret;
	}
} Conv;

int main() {
	fastio;
	for (string s; cin >> s && s != "BYE";) {
		s.pop_back(); s[s.find('+')] = ' ';
		stringstream in(s);
		string a, b; in >> a >> b;
		cout << a << '+' << b << '=' << Conv(Conv(a) + Conv(b)) << '\n';
	}
}