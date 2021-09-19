#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
using namespace std;

constexpr int SZ = 1 << 16;

int main() {
    struct stat st; fstat(0, &st);
	char w[SZ], *p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0), *q = w;
	auto ReadInt = [&]() {
		int ret = 0;
		for (char c = *p++; c & 16; ret = 10 * ret + (c & 15), c = *p++);
		return ret;
	};
    auto H = [&]() -> uint32_t {
        uint32_t ret = 0;
        for (char c = *p++; isalpha(c); c = *p++) {
            ret = (ret ^ (ret >> 30)) * c;
            ret = (ret ^ (ret >> 27)) + c;
        }
        return ret;
    };
    auto WriteInt = [&](int n) {
        if (q - w + 32 >= SZ) write(1, w, q - w), q = w;
        int sz = 1, t = n;
        for (; t >= 10; t /= 10) sz++;
        for (int i = sz; i --> 0; n /= 10) q[i] = n % 10 | 48;
        q += sz;
    };
    auto WriteStr = [&](char* p) {
        if (q - w + 32 >= SZ) write(1, w, q - w), q = w;
        for (char c = *p++; isalpha(c); c = *p++) *q++ = c;
    };

	int n = ReadInt(), m = ReadInt();
	char* s[n + 1];
    unordered_map<uint32_t, int> M;
	for (int i = 1; i <= n; i++) s[i] = p, M[H()] = i;

	while (m--) {
		if (isdigit(*p)) WriteStr(s[ReadInt()]), *q++ = '\n';
		else WriteInt(M[H()]), *q++ = '\n';
	}
    write(1, w, q - w);
}