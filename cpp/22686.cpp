#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int conv[128];

void Init() {
    conv['L'] = 0;
    conv['U'] = conv['D'] = 1;
    conv['R'] = 2;
}

bool Sol(const string& s) {
    bool t1{}, t2{};
    for (int i = 1; i < s.size(); i++) {
        if (s[i - 1] == s[i]) return 0;
        if (i & 1 && conv[s[i - 1]] < conv[s[i]]) t1 = 1;
        if (i & 1 && conv[s[i - 1]] > conv[s[i]]) t2 = 1;
    }
    return !(t1 & t2);
}

int main() {
    fastio;
    int N; cin >> N;
    for (Init(); N--;) {
        string s; cin >> s;
        cout << (Sol(s) ? "Yes" : "No") << '\n';
    }
}