#include "CUSTOM_BITSET.h"

constexpr unsigned long long DB[] = {
    0x5555555555555555ULL, 0x3333333333333333ULL,
    0x0F0F0F0F0F0F0F0FULL, 0x00FF00FF00FF00FFULL,
    0x0000FFFF0000FFFFULL, 0x00000000FFFFFFFFULL,
};

inline CUSTOM_BITSET Add(CUSTOM_BITSET& a, CUSTOM_BITSET& b, int cnt) {
    static CUSTOM_BITSET c;
    while (cnt--) {
        c = a; c &= b; c <<= 1; c.setbit(0, 0);
        a ^= b; b = c;
    }
    return a;
}

int __builtout_popcount(CUSTOM_BITSET& a) {
	int ret = 0; CUSTOM_BITSET mask, b;
    for (int i = 0; i < 16; i++) {
        if (i < 6) for (int j = 0; j < 1024; j++) mask.setvalue(j, DB[i]);
        else for (int j = 0; j < 1024; j++) mask.setvalue(j, j >> i - 6 & 1 ? 0 : -1);
        b = a; b &= mask; a >>= 1 << i; a &= mask;
        a = Add(a, b, i + 2);
    }
    for (int i = 0; i < 17; i++) if (a.getbit(i)) ret |= 1 << i;
    return ret;
}