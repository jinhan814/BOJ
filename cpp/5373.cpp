#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Rubiks {
private:
	enum class Face { L, F, R, B, U, D };
	struct Info     { int face, x, y; };
	char v[6][3][3];

	int Conv(const char c) const {
		if (c == 'L') return (int)Face::L;
		if (c == 'F') return (int)Face::F;
		if (c == 'R') return (int)Face::R;
		if (c == 'B') return (int)Face::B;
		if (c == 'U') return (int)Face::U;
		if (c == 'D') return (int)Face::D;
	}

	void Rotate_Face(const int face, const int dir) {
		static int t[3][3];
		if (dir == 1) { // cw
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) t[i][j] = v[face][i][j];
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) v[face][j][2 - i] = t[i][j];
		}
		else { // ccw
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) t[i][j] = v[face][i][j];
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) v[face][2 - j][i] = t[i][j];
		}
	}

	void Swap(const Info a, const Info b, const Info c, const Info d, const int dir) {
		const int t = v[a.face][a.x][a.y];
		if (dir == 1) {
			v[a.face][a.x][a.y] = v[b.face][b.x][b.y];
			v[b.face][b.x][b.y] = v[c.face][c.x][c.y];
			v[c.face][c.x][c.y] = v[d.face][d.x][d.y];
			v[d.face][d.x][d.y] = t;
		}
		else {
			v[a.face][a.x][a.y] = v[d.face][d.x][d.y];
			v[d.face][d.x][d.y] = v[c.face][c.x][c.y];
			v[c.face][c.x][c.y] = v[b.face][b.x][b.y];
			v[b.face][b.x][b.y] = t;
		}
	}

public:
	Rubiks() : v{} { Init(); }

	void Init() {
		for (int face = 0; face < 6; face++) {
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
				v[face][i][j] = "grbowy"[face];
			}
		}
	}

	void Rotate(const string& s) {
        const int face = Conv(s[0]), dir = s[1] == '+' ? 1 : -1;
		Rotate_Face(face, dir);
		if (face == (int)Face::F) {
			Swap({ 4, 2, 0 }, { 0, 2, 2 }, { 5, 0, 2 }, { 2, 0, 0 }, dir);
			Swap({ 4, 2, 1 }, { 0, 1, 2 }, { 5, 0, 1 }, { 2, 1, 0 }, dir);
			Swap({ 4, 2, 2 }, { 0, 0, 2 }, { 5, 0, 0 }, { 2, 2, 0 }, dir);
		}
		else if (face == (int)Face::B) {
			Swap({ 4, 0, 0 }, { 2, 0, 2 }, { 5, 2, 2 }, { 0, 2, 0 }, dir);
			Swap({ 4, 0, 1 }, { 2, 1, 2 }, { 5, 2, 1 }, { 0, 1, 0 }, dir);
			Swap({ 4, 0, 2 }, { 2, 2, 2 }, { 5, 2, 0 }, { 0, 0, 0 }, dir);
		}
		else if (face == (int)Face::L) {
			Swap({ 4, 0, 0 }, { 3, 2, 2 }, { 5, 0, 0 }, { 1, 0, 0 }, dir);
			Swap({ 4, 1, 0 }, { 3, 1, 2 }, { 5, 1, 0 }, { 1, 1, 0 }, dir);
			Swap({ 4, 2, 0 }, { 3, 0, 2 }, { 5, 2, 0 }, { 1, 2, 0 }, dir);
		}
		else if (face == (int)Face::R) {
			Swap({ 4, 0, 2 }, { 1, 0, 2 }, { 5, 0, 2 }, { 3, 2, 0 }, dir);
			Swap({ 4, 1, 2 }, { 1, 1, 2 }, { 5, 1, 2 }, { 3, 1, 0 }, dir);
			Swap({ 4, 2, 2 }, { 1, 2, 2 }, { 5, 2, 2 }, { 3, 0, 0 }, dir);
		}
		else if (face == (int)Face::U) {
			Swap({ 0, 0, 0 }, { 1, 0, 0 }, { 2, 0, 0 }, { 3, 0, 0 }, dir);
			Swap({ 0, 0, 1 }, { 1, 0, 1 }, { 2, 0, 1 }, { 3, 0, 1 }, dir);
			Swap({ 0, 0, 2 }, { 1, 0, 2 }, { 2, 0, 2 }, { 3, 0, 2 }, dir);
		}
		else if (face == (int)Face::D) {
			Swap({ 0, 2, 0 }, { 3, 2, 0 }, { 2, 2, 0 }, { 1, 2, 0 }, dir);
			Swap({ 0, 2, 1 }, { 3, 2, 1 }, { 2, 2, 1 }, { 1, 2, 1 }, dir);
			Swap({ 0, 2, 2 }, { 3, 2, 2 }, { 2, 2, 2 }, { 1, 2, 2 }, dir);
		}
	}

	void Print() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) cout << v[4][i][j];
			cout << '\n';
		}
	}
};

int main() {
	fastio;
	int N; cin >> N;
    while (N--) {
		Rubiks R;
        int q; cin >> q;
		while (q--) { string s; cin >> s; R.Rotate(s); }
		R.Print();
	}
}