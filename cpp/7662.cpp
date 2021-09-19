#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

template<typename T = int, typename F = less<T>>
struct Priority_Queue {
	Priority_Queue() = default;
	Priority_Queue(const F& f) : insert(f), erase(f) {}
	T Top() { __Erase(); return insert.top(); }
	void Insert(T val) { __Erase(); insert.push(val); }
	void Erase(T val) { __Erase(); erase.push(val); }
	size_t size() { __Erase(); return insert.size(); }
private:
	priority_queue<T, vector<T>, F> insert, erase;
	void __Erase() {
		while (erase.size() && insert.top() == erase.top())
			insert.pop(), erase.pop();
	}
};

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		Priority_Queue<int, less<int>> PQ1; // max_heap
		Priority_Queue<int, greater<int>> PQ2; // min_heap

		while (n--) {
			char c; int t; cin >> c >> t;
			if (c == 'D') {
				if (t == 1 && PQ1.size()) PQ2.Erase(PQ1.Top()), PQ1.Erase(PQ1.Top());
				if (t == -1 && PQ2.size()) PQ1.Erase(PQ2.Top()), PQ2.Erase(PQ2.Top());
			}
			else PQ1.Insert(t), PQ2.Insert(t);
		}

		if (!PQ1.size()) cout << "EMPTY" << '\n';
		else cout << PQ1.Top() << ' ' << PQ2.Top() << '\n';
	}
}