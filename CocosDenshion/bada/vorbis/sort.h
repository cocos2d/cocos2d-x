#ifndef SORT_H
#define SORT_H

typedef int (*CCDataCompareFunc)(const void* ctx, const void* data);

#ifdef __cplusplus
extern "C" {
#endif

int cc_qsort(void** array, int nr, CCDataCompareFunc cmp);

#ifdef __cplusplus
}
#endif

#endif/*SORT_H*/

