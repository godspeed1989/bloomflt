#include "bloomflt.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NUM_HASH    8

bloom_filter* create_bfilter(unsigned long size)
{
    bloom_filter* bFilter;
	bFilter = (bloom_filter*)malloc(sizeof(bloom_filter));
    assert(bFilter);

    bFilter->filter = (filter_t*)malloc(size*sizeof(filter_t));
    assert(bFilter->filter);
    memset(bFilter->filter, 0, size*sizeof(filter_t));

    bFilter->size = size;
    return bFilter;
}

void destroy_bfilter(bloom_filter* bFilter)
{
    if(bFilter->filter) free(bFilter->filter);
    if(bFilter) free(bFilter);
}

// Computes our hashes
static void bfilter_compute_hashes(const char *key, unsigned int *hashes)
{
    hashes[0] = SDBMHash (key);
    hashes[1] = RSHash (key);
    hashes[2] = JSHash (key);
    hashes[3] = PJWHash (key);
    hashes[4] = ELFHash (key);
    hashes[5] = BKDRHash (key);
    hashes[6] = DJBHash (key);
    hashes[7] = APHash (key);
}

#define COMPUTE_HASHES(key, hashes)                 \
    do {                                            \
        unsigned int i;                             \
        bfilter_compute_hashes(key, hashes);        \
        for (i = 0; i < NUM_HASH; i++)              \
            hashes[i] = hashes[i] % bFilter->size;  \
    }while(0);

// 加入
void bfilter_add(const bloom_filter* bFilter, const char *key)
{
    unsigned int i;
    unsigned int hashes[NUM_HASH];
    COMPUTE_HASHES(key, hashes);
    for (i = 0; i < NUM_HASH; i++)
        if (bFilter->filter[hashes[i]] != (filter_t)-1)
            bFilter->filter[hashes[i]]++;
        else
            assert(0); // overflow
}

// 检测
int bfilter_check(const bloom_filter* bFilter, const char *key)
{
    unsigned int i;
	unsigned int hashes[NUM_HASH];
    COMPUTE_HASHES(key, hashes);
    for (i = 0; i < NUM_HASH; i++)
        if (bFilter->filter[hashes[i]] == 0)
            return 0;
    return 1;
}

// !!!确认key在集合中才能调用bfilter_del()函数!!!
void bfilter_del(const bloom_filter* bFilter, const char *key)
{
    unsigned int i;
    unsigned int hashes[NUM_HASH];
    COMPUTE_HASHES(key, hashes);
    for (i = 0; i < NUM_HASH; i++)
        if (bFilter->filter[hashes[i]] != 0)
            bFilter->filter[hashes[i]]--;
        else
            assert(0); // del non-exist
}
