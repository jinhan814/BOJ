#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	vector<int> T, D;
	for (int i = 0; i < n; i++) {
		char c; int t; cin >> c >> t;
		(c == 'T' ? T : D).push_back(t);
	}
	sort(T.begin(), T.end()); sort(D.begin(), D.end());
	while (D.size() && D.back() >= 1000) D.pop_back(); D.push_back(1000);

	auto Sol = [&]() -> int {
		double t = 0, pos = 0;
		for (int i = 0, j = 0, speed = 1; pos < 1000; speed++) {
			if (i < T.size() && j < D.size()) {
				if ((T[i] - t) / speed > D[j] - pos) {
					t += (D[j] - pos) * speed;
					pos = D[j++];
				}
				else {
					pos += (T[i] - t) / speed;
					t = T[i++];
				}
			}
			else if (i < T.size()) {
				pos += (T[i] - t) / speed;
				t = T[i++];
			}
			else {
				t += (D[j] - pos) * speed;
				pos = D[j++];
			}
		}
		return t + 0.5;
	};

	cout << Sol() << '\n';
}