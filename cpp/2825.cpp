#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;

int main() {
    struct stat st; fstat(0, &st);
    char* p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
	auto ReadInt = [&]() {
		int ret = 0;
        for (char c = *p++; c & 16; ret = 10 * ret + (c & 15), c = *p++);
		return ret;
	};
    auto F = [&]() {
        int ret = 0;
        for (char c = *p++; c & 16; ret |= 1 << (c & 15), c = *p++);
        return ret;
    };
    
	int n = ReadInt(), cnt[1 << 10]{}; int64_t ans = 0;
	for (int i = 0; i < n; i++) cnt[F()]++;
	for (int i = 0; i < 1 << 10; i++) for (int j = 0; j < 1 << 10; j++)
		if (i & j) ans += 1LL * cnt[i] * cnt[j];
	cout << (ans - n >> 1) << '\n';
}