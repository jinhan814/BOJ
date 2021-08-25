#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Calendar {
    int Month[13]{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int operator()(int y, int m) {
        if ((y % 4 == 0 && y % 100 || y % 400 == 0) && m == 2) return 29;
        return Month[m];
    };
} DayRange;

bool f(const string& s) {
    int ret = 0;
    for (int i = 0; i < 8; i++) ret += (s[i] & 15) * (s[i] & 15);
    return ret % 7 == (s.back() & 15);
}

bool Sol(string s) {
    if (s[7] != '1' && s[7] != '6' && s[7] != '9') return 0;
    int d = stoi(s.substr(0, 2));
    int m = stoi(s.substr(2, 2));
    int y = stoi(s.substr(4, 3)); y += y < 600 ? 2000 : 1000;
    if (m < 1 or m > 12) return 0;
    if (d < 1 or d > DayRange(y, m)) return 0;
    return f(s);
}

int main() {
    fastio;
    for (string s; cin >> s; cout << Sol(s) << '\n');
}