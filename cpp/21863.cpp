#include "CUSTOM_BITSET.h"

CUSTOM_BITSET Sum(CUSTOM_BITSET& a, CUSTOM_BITSET& b, int d) {
    CUSTOM_BITSET c = a; c &= b; c <<= 1; c.setbit(0, 0);
    CUSTOM_BITSET s = a; s ^= b;
    if (d) return Sum(s, c, d - 1);
    return s ^= c, s;
}

int __builtout_popcount(CUSTOM_BITSET& a) {
	int ret = 0;
    for (int i = 0; i < 16; i++) {
        CUSTOM_BITSET mask;
        for (int j = 0; j < 65536; j++) mask.setbit(j, !(j >> i & 1));
        CUSTOM_BITSET t1 = a, t2 = a; t1 >>= 1 << i; t1 &= mask; t2 &= mask;
        a = Sum(t1, t2, i + 1);
    }
    for (int i = 0; i < 17; i++) if (a.getbit(i)) ret |= 1 << i;
    return ret;
}