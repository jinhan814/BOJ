#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Rubiks {
private:
	enum class Face { L, F, R, B, U, D };
	struct Info     { int face, x, y; };
	char v[6][3][3];

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
	Rubiks() : v{} {}

	void Input() {
		for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
			cin >> v[4][i][j];
		}
		for (int i = 0; i < 3; i++) for (int k = 0; k < 4; k++) for (int j = 0; j < 3; j++) {
			cin >> v[k][i][j];
		}
		for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
			cin >> v[5][i][j];
		}
	}

	void Rotate(int face, int dir) {
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
			cout << "      ";
			for (int j = 0; j < 3; j++) cout << v[4][i][j] << ' ';
			cout << '\n';
		}
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 4; k++) for (int j = 0; j < 3; j++) cout << v[k][i][j] << ' ';
			cout << '\n';
		}
		for (int i = 0; i < 3; i++) {
			cout << "      ";
			for (int j = 0; j < 3; j++) cout << v[5][i][j] << ' ';
			cout << '\n';
		}
	}
};

int main() {
	fastio;
	int N; cin >> N;
	for (int c = 1, q; c <= N; c++) {
		Rubiks R; R.Input();
		for (cin >> q; q--;) {
			int face, dir; cin >> face >> dir;
			R.Rotate(face, dir);
		}
		cout << "Scenario #" << c << ":\n";
		R.Print();
		cout << '\n';
	}
}