#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;

int main() {
    struct stat st; fstat(0, &st);
	char *p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
	auto ReadInt = [&]() {
		int ret = 0;
		for (char c = *p++; c & 16; ret = 10 * ret + (c & 15), c = *p++);
		return ret;
	};
	auto f = [&]() -> bool {
		for (char c = *p++; c & 16; c = *p++);
		return p[-2] & 1;
	};

	int n = ReadInt(), k = ReadInt(), mx = 0;
    bitset<1'000'000> v;
    for (int i = 0; i < n; i++) v[i] = f();

	for (int l = 0, r = 0, sum = 0; l < n;) {
        while (r < n && sum + v[r] <= k) sum += v[r++];
		mx = max(mx, r - l - sum); sum -= v[l++];
	}
	cout << mx << '\n';
}