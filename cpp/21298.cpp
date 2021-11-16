#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

/* BASIC INTERFACE */

using ll  = long long;
using i11 = array<int, 11>;

istream& operator>> (istream& in, i11& x) {
	for (int i = 0; i < 11; i++) in >> x[i];
	return in;
}

struct Converter {
	i11 I, state, inv; // base
	i11 operator() (int n) {
		i11 ret;
		for (int i = 0; i < 11; i++) inv[state[i]] = i;
		for (int i = 11; i --> 0;) ret[inv[i]] = n % I[i], n /= I[i];
		return ret;
	}
	int operator() (i11 x) {
		int ret = 0;
		for (int i = 0; i < 11; i++) inv[state[i]] = i;
		for (int i = 0; i < 11; i++) ret = ret * I[i] + x[inv[i]];
		return ret;
	}
} Conv;

void Increment(const i11& a, const i11& b, i11& x) {
	x[10]++;
	for (int i = 11; --i;) {
		if (x[i] > b[i]) x[i] = a[i], x[i - 1]++;
		else return;
	}
}


/* ALGORITHM */

int n = 1, idx[55][2];
ll v[111'111], w[111'111];

void Init() {
	for (int i = 0; i < 11; i++) Conv.state[i] = i;
	for (int i = 0, t = 0; i < 11; i++) {
		for (int j = i + 1; j < 11; j++, t++)
			idx[t][0] = i, idx[t][1] = j;
	}
}

void Query1(int op, const i11& a, const i11& b) {
	memcpy(w, v, sizeof v); op--;
	for (i11 i = a; i[0] <= b[0]; Increment(a, b, i)) {
		i11 x = i; x[op] = a[op] + b[op] - x[op];
		v[Conv(x)] = w[Conv(i)];
	}
}

void Query2(int op, const i11& a, const i11& b) {
	memcpy(w, v, sizeof v); op -= 12;
	const int t1 = idx[op][0], t2 = idx[op][1];
	if (b[t1] - a[t1] < b[t2] - a[t2]) {
		const int t = b[t1] - a[t1] + 1 >> 1;
		for (i11 i = a; i[0] <= b[0]; Increment(a, b, i)) {
			i11 x = i;
			if (x[t1] < a[t1] + t &&
				x[t2] - x[t1] >= a[t2] - a[t1] &&
				x[t1] + x[t2] < a[t1] + b[t2]) x[t2]++;
			else if (
				x[t1] >= a[t1] + t &&
				x[t2] - x[t1] <= b[t2] - b[t1] &&
				x[t1] + x[t2] > b[t1] + a[t2]) x[t2]--;
			else if (x[t2] < a[t2] + t) x[t1]--;
			else x[t1]++;
			v[Conv(x)] = w[Conv(i)];
		}
	}
	else {
		const int t = b[t2] - a[t2] + 1 >> 1;
		for (i11 i = a; i[0] <= b[0]; Increment(a, b, i)) {
			i11 x = i;
			if (x[t2] < a[t2] + t &&
				x[t2] - x[t1] < a[t2] - a[t1] &&
				x[t1] + x[t2] <= b[t1] + a[t2]) x[t1]--;
			else if (
				x[t2] >= a[t2] + t &&
				x[t2] - x[t1] > b[t2] - b[t1] &&
				x[t1] + x[t2] >= a[t1] + b[t2]) x[t1]++;
			else if (x[t1] < a[t1] + t) x[t2]++;
			else x[t2]--;
			v[Conv(x)] = w[Conv(i)];
		}
	}
}

void Query3(int op) {
	op -= 67;
	swap(Conv.state[idx[op][0]], Conv.state[idx[op][1]]);
}


/* MAIN FUNCTION */

int main() {
	fastio;
	Init(); cin >> Conv.I;
	for (int i = 0; i < 11; i++) n *= Conv.I[i];
	for (int i = 0; i < n; i++) cin >> v[i];

	int q; cin >> q;
	while (q--) {
		int op; cin >> op;
		if (op <= 66) {
			i11 a, b; cin >> a >> b;
			for (int i = 0; i < 11; i++) a[i]--, b[i]--;
			if (op <= 11) Query1(op, a, b);
			else Query2(op, a, b);
		}
		else Query3(op);
	}

	i11 a = Conv(0), b = Conv(n - 1), cur = Conv(0);
	for (int i = 0; i < 11; i++) cout << Conv.I[Conv.state[i]] << ' '; cout << '\n';
	for (int i = 0; i < n; i += Conv.I[Conv.state[10]]) {
		for (int j = 0; j < Conv.I[Conv.state[10]]; j++, Increment(a, b, cur))
			cout << v[Conv(cur)] << ' ';
		cout << '\n';
	}
}