#ifndef ARB_HASH_INCLUDED_H
#define ARB_HASH_INCLUDED_H

#include <stdint.h>

typedef struct ArbHashBlock {
    uint64_t count;
    uint8_t* data;
} AHBlock;

static inline void arb_hash(const AHBlock in, AHBlock out, const uint64_t rounds);
static inline void arb_hash(const AHBlock in, AHBlock out, const uint64_t rounds) {
    const uint_fast8_t shifts[5] = {1, 2, 3, 5, 7};
    if (in.data && out.data && out.count >= in.count && in.count >= 3) {
        for (uint_fast64_t i = 0; i < in.count; i++) {
            out.data[i] = in.data[i];
        }
        for (uint_fast64_t rnd = 0; rnd < rounds; rnd++) {
            for (uint_fast64_t bshft = 0; bshft < in.count; bshft++) {
                for (uint_fast64_t elem = 0; elem < in.count; elem++) {
                    const uint_fast8_t s = shifts[(bshft + elem) % 5];
                    uint8_t *const restrict a = out.data + elem;
                    uint8_t *const restrict b = out.data + (elem + 1) % in.count;
                    uint8_t *const restrict c = out.data + (elem + 2) % in.count;
                    *a += *b;
                    *c ^= *a;
                    *c = (uint8_t)((*c << s) | (*c >> (8 - s)));
                }
            }
        }
        for (uint_fast64_t i = 0; i < in.count; i++) {
            out.data[i] ^= in.data[i];
        }
    }
}

#endif
