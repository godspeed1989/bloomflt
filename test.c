#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bloomflt.h"

#define NUM_ITEMS       (10000000)
#define NUM_BUCKETS     (NUM_ITEMS * 20)

int main()
{
    bloom_filter *flt;
    flt = create_bfilter(NUM_BUCKETS);

    destroy_bfilter(flt);    
    return 0;
}
