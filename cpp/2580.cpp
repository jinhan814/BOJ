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

board Sol(const board& v) {
	vector<vector<int>> info;
	vector<tuple<int, int, int>> pos;
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) {
		auto MakeRow = [&](int k) {
			vector<int> row(324);
			row[i * 9 + j] = 1;
			row[81 + i * 9 + k] = 1;
			row[81 * 2 + j * 9 + k] = 1;
			row[81 * 3 + (i / 3 * 3 + j / 3) * 9 + k] = 1;
			info.push_back(row);
			pos.push_back({ i, j, k });
		};
		if (v[i][j]) MakeRow(v[i][j] - 1);
		else for (int k = 0; k < 9; k++) MakeRow(k);
	}
	board ret;
	for (auto& i : DLX::Sol(info)) {
		const auto& [x, y, k] = pos[i];
		ret[x][y] = k + 1;
	}
	return ret;
}

int main() {
	fastio;
	board v;
	for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) cin >> v[i][j];
	auto ans = Sol(v);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) cout << ans[i][j] << ' ';
		cout << '\n';
	}
}