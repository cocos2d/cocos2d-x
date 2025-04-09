#ifndef COCOS_CUTILS_BITOPS_H
#define COCOS_CUTILS_BITOPS_H

#include <stdbool.h>
#include <string.h>
#include <strings.h>



#ifdef	__cplusplus
extern "C" {
#endif

static inline int popcount(unsigned int x) {
    return __builtin_popcount(x);
}

static inline int popcountl(unsigned long x) {
    return __builtin_popcountl(x);
}

static inline int popcountll(unsigned long long x) {
    return __builtin_popcountll(x);
}

#ifdef	__cplusplus
}
#endif

#endif /* COCOS_CUTILS_BITOPS_H */
