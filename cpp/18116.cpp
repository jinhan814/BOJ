#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;

template<size_t sz>
struct UnionFind {
    int par[sz];
    UnionFind() { memset(par, -1, sizeof par); }
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a == b) return;
        par[a] += par[b], par[b] = a;
    }
};

int main() {
    struct stat st; fstat(0, &st);
	char *p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
	auto ReadInt = [&]() {
		int ret = 0;
		for (char c = *p++; c & 16; ret = 10 * ret + (c & 15), c = *p++);
		return ret;
	};
    
    UnionFind<1'000'001> UF;
	for (int q = ReadInt(); q--;) {
		char c = *p++; p++;
		if (c == 'I') UF.Union(ReadInt(), ReadInt());
		else cout << -UF.par[UF.Find(ReadInt())] << '\n';
	}
}