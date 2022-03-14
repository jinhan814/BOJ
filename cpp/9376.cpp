#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i16 = short;
using vi = vector<i16>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using pip = pair<i16, pii>;
constexpr i16 INF = 1e4;

struct Board {
	int n, m;
	vector<string> v;
	Board(int n, int m) : n(n), m(m), v(n) {}
	string& operator[] (int i) { return v[i]; }
	const string& operator[] (int i) const { return v[i]; }
};

istream& operator>> (istream& in, Board& v) {
	for (int i = 0; i < v.n; i++) in >> v[i];
	return in;
}

vvi Dijkstra(const Board& B, const vector<pii>& st) {
	const int n = B.n, m = B.m;
	vvi dist(n, vi(m, INF));
	priority_queue<pip, vector<pip>, greater<>> PQ;
	for (auto& i : st) PQ.push({ dist[i.first][i.second] = B[i.first][i.second] == '#', i });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur.first][cur.second] != cdist) continue;
		for (int d = 0; d < 4; d++) {
			const int nx = cur.first + "1012"[d] - '1';
			const int ny = cur.second + "2101"[d] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m || B[nx][ny] == '*') continue;
			const int ndist = cdist + (B[nx][ny] == '#');
			if (dist[nx][ny] > ndist) PQ.push({ dist[nx][ny] = ndist, { nx, ny } });
		}
	}
	return dist;
}

vvi GetD1(const Board& B) {
	const int n = B.n, m = B.m;
	vector<pii> st;
	for (int i = 0; i < n; i++) {
		if (B[i][0] != '*') st.push_back({ i, 0 });
		if (B[i][m - 1] != '*') st.push_back({ i, m - 1 });
	}
	for (int i = 1; i < m - 1; i++) {
		if (B[0][i] != '*') st.push_back({ 0, i });
		if (B[n - 1][i] != '*') st.push_back({ n - 1, i });
	}
	return Dijkstra(B, st);
}

vvi GetD2(const Board& B, const pii& p) {
	vector<pii> st{ p };
	return Dijkstra(B, st);
}

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, m; cin >> n >> m;
		Board B(n, m); cin >> B;
		vector<pii> pos;
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)	if (B[i][j] == '$') pos.push_back({ i, j });
		auto d1 = GetD1(B);
		auto d2 = GetD2(B, pos[0]);
		auto d3 = GetD2(B, pos[1]);
		int res = d1[pos[0].first][pos[0].second] + d1[pos[1].first][pos[1].second];
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
			if (d1[i][j] == INF || d2[i][j] == INF || d3[i][j] == INF) continue;
			int dist = d1[i][j] + d2[i][j] + d3[i][j];
			if (B[i][j] == '#') dist -= 2;
			res = min(res, dist);
		}
		cout << res << '\n';
	}
}