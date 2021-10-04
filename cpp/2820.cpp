#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;

template<size_t sz>
struct FenwickTree {
	int tree[sz + 1];
	void update(int i, int val) {
		for (; i <= sz; i += i & -i) tree[i] += val;
	}
	int query(int i) {
		int ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
};

FenwickTree<1 << 19> FT;
int n, q, in[1 << 19], out[1 << 19], v[1 << 19];
vector<int> adj[1 << 19];

void DFS(int cur = 1) {
	static int temp = 0;
	in[cur] = ++temp;
	for (auto nxt : adj[cur]) DFS(nxt);
	out[cur] = temp;
}

int main() {
    struct stat st; fstat(0, &st);
	char* p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
	auto ReadInt = [&]() {
		int ret = 0; char c = *p++, flag = 0;
        if (c == '-') c = *p++, flag = 1;
		for (; c & 16; ret = 10 * ret + (c & 15), c = *p++);
		return flag ? -ret : ret;
	};

	n = ReadInt(), q = ReadInt();
	for (int i = 1, t = 0; i <= n; i++) {
        v[i] = ReadInt();
        if (i > 1) t = ReadInt();
		adj[t].push_back(i);
	}
    DFS();

	for (int i = 1; i <= n; i++) {
		FT.update(in[i], v[i]);
		FT.update(in[i] + 1, -v[i]);
	}

	while (q--) {
		char c = *p++; p++;
		if (c == 'p') {
			int a = ReadInt(), b = ReadInt();
			FT.update(in[a] + 1, b);
			FT.update(out[a] + 1, -b);
		}
		else cout << FT.query(in[ReadInt()]) << '\n';
	}
}