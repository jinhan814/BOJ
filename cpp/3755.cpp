#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

template<typename T = int, typename F = less<T>>
struct Priority_queue {
	Priority_queue() = default;
	Priority_queue(const F& f) : insert(f), erase(f) {}
	T Top() { __Erase(); return insert.top(); }
	void Insert(T val) { __Erase(); insert.push(val); }
	void Erase(T val) { __Erase(); erase.push(val); }
	size_t size() { __Erase(); return insert.size(); }
	bool empty() { __Erase(); return insert.empty(); }
private:
	priority_queue<T, vector<T>, F> insert, erase;
	void __Erase() {
		while (erase.size() && insert.top() == erase.top())
			insert.pop(), erase.pop();
	}
};

int main() {
	fastio;
	Priority_queue<pii> PQ1;
	Priority_queue<pii, greater<pii>> PQ2;
	for (int t, a, b; cin >> t && t;) {
		if (t == 1) cin >> a >> b, PQ1.Insert({ b, a }), PQ2.Insert({ b, a });
		else if (t == 2) {
			if (PQ1.empty()) cout << 0 << '\n';
			else cout << PQ1.Top().second << '\n', PQ2.Erase(PQ1.Top()), PQ1.Erase(PQ1.Top());
		}
		else if (t == 3) {
			if (PQ2.empty()) cout << 0 << '\n';
			else cout << PQ2.Top().second << '\n', PQ1.Erase(PQ2.Top()), PQ2.Erase(PQ2.Top());
		}
	}
}