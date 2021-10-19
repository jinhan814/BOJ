#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;

int n, mx, val, v[1'000'001], pSum[1'000'001];

int main() {
    struct stat st; fstat(0, &st);
	char* p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
	auto ReadInt = [&]() {
		int ret = 0;
		for (char c = *p++; c & 16; ret = 10 * ret + (c & 15), c = *p++);
		return ret;
	};

	n = ReadInt();
	for (int i = 1; i <= n; i++) pSum[i] = __gcd(pSum[i - 1], v[i] = ReadInt());
    for (int i = n, t = 0; i >= 1; t = __gcd(v[i--], t)) {
        const int g = __gcd(pSum[i - 1], t);
        if (g % v[i] && mx < g) mx = g, val = v[i];
    }
	if (mx <= pSum[n]) cout << -1 << '\n';
	else cout << mx << ' ' << val << '\n';
}