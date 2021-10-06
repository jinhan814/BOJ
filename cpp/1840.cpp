#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;
struct Info { int x, y, val; };
using board = array<array<int, 9>, 9>;

namespace DLX {
	struct node {
		int row, sz;
		node* column;
		node* up, * down;
		node* left, * right;
	};
	void Cover(node* c) {
		c->right->left = c->left;
		c->left->right = c->right;
		for (node* it = c->down; it != c; it = it->down) {
			for (node* jt = it->right; jt != it; jt = jt->right) {
				jt->down->up = jt->up;
				jt->up->down = jt->down;
				jt->column->sz--;
			}
		}
	}
	void Uncover(node* c) {
		for (node* it = c->up; it != c; it = it->up) {
			for (node* jt = it->left; jt != it; jt = jt->left) {
				jt->down->up = jt;
				jt->up->down = jt;
				jt->column->sz++;
			}
		}
		c->right->left = c;
		c->left->right = c;
	}
	bool Search(node* head, vector<int>& ret) {
		if (head->right == head) return 1;
		node* ptr = nullptr; int low = INF;
		for (node* it = head->right; it != head; it = it->right) {
			if (it->sz < low) {
				if (it->sz == 0) return 0;
				low = it->sz;
				ptr = it;
			}
		}
		Cover(ptr);
		for (node* it = ptr->down; it != ptr; it = it->down) {
			ret.push_back(it->row);
			for (node* jt = it->right; jt != it; jt = jt->right) Cover(jt->column);
			if (Search(head, ret)) return 1;
			else {
				ret.pop_back();
				for (node* jt = it->left; jt != it; jt = jt->left) Uncover(jt->column);
			}
		}
		Uncover(ptr);
		return 0;
	}
	vector<int> Sol(vector<vector<int>> v) {
		const int n = v[0].size();
		vector<node> column(n); node head;
		head.right = &column[0];
		head.left = &column[n - 1];
		for (int i = 0; i < n; i++) {
			column[i].sz = 0;
			column[i].up = &column[i];
			column[i].down = &column[i];
			if (i == 0) column[i].left = &head;
			else column[i].left = &column[i - 1];
			if (i == n - 1) column[i].right = &head;
			else column[i].right = &column[i + 1];
		}
		vector<node*> nodes;
		for (int i = 0; i < v.size(); i++) {
			node* last = nullptr;
			for (int j = 0; j < n; j++) if (v[i][j]) {
				node* now = new node;
				now->row = i;
				now->column = &column[j];
				now->up = column[j].up;
				now->down = &column[j];
				if (last) {
					now->left = last;
					now->right = last->right;
					last->right->left = now;
					last->right = now;
				}
				else {
					now->left = now;
					now->right = now;
				}
				column[j].up->down = now;
				column[j].up = now;
				column[j].sz++;
				last = now;
				nodes.push_back(now);
			}
		}
		vector<int> ret;
		Search(&head, ret);
		for (node* ptr : nodes) delete ptr;
		return ret;
	}
}

bool Check(const board& B) {
	for (int i = 0; i < 9; i++) {
		int t = 0;
		for (int j = 0; j < 9; j++) t |= 1 << B[i][j];
		if (t != 0b1111111110) return 0;
	}
	for (int i = 0; i < 9; i++) {
		int t = 0;
		for (int j = 0; j < 9; j++) t |= 1 << B[j][i];
		if (t != 0b1111111110) return 0;
	}
	for (int x = 0; x < 9; x += 3) for (int y = 0; y < 9; y += 3) {
		int t = 0;
		for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) t |= 1 << B[x + i][y + j];
		if (t != 0b1111111110) return 0;
	}
	return 1;
}

bool IsValid(const board& B) {
	vector<vector<int>> v;
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) {
		auto MakeRow = [&](int k) {
			vector<int> row(324);
			row[i * 9 + j] = 1;
			row[81 + i * 9 + k] = 1;
			row[81 * 2 + j * 9 + k] = 1;
			row[81 * 3 + (i / 3 * 3 + j / 3) * 9 + k] = 1;
			v.push_back(row);
		};
		if (B[i][j]) MakeRow(B[i][j] - 1);
		else for (int k = 0; k < 9; k++) MakeRow(k);
	}
	auto res = DLX::Sol(v);
	return DLX::Sol(v).size() == 81;
}

int main() {
	fastio;
	Info I[81]; board st{};
	int pos = -1;

	for (int i = 0; i < 81; i++) {
		auto& [x, y, val] = I[i];
		cin >> x >> y >> val; --x, --y;
		if (pos == -1 && st[x][y]) pos = i + 1;
		st[x][y] = val;
	}

	if (~pos) return !(cout << pos << '\n');
	if (Check(st)) return !(cout << -1 << '\n');

	int lo = 0, hi = 81;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		board cur{};
		for (int i = 0; i < mid; i++) {
			const auto& [x, y, val] = I[i];
			cur[x][y] = val;
		}
		if (IsValid(cur)) lo = mid;
		else hi = mid;
	}
	cout << hi << '\n';
}