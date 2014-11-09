#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bloomflt.h"

#define NUM_ITEMS       (32767)
#define NUM_BUCKETS     (NUM_ITEMS * 8)

#define STR_LEN         (32)
static char filter_contents[NUM_ITEMS][STR_LEN];
static char   test_contents[NUM_ITEMS][STR_LEN];

static void randstr(char *s, int len)
{
    int i;
    for (i = 0; i < len-1; i++)
        s[i] = 'a' + rand() % ('z'-'a'+1);
    s[len-1] = '\0';
}

static int brute_force_search(const char *s)
{
    unsigned int i;
    for (i = 0; i < NUM_ITEMS; i++)
        if (!strcmp(filter_contents[i], s))
            return 1;
    return 0;
}

int main()
{
    unsigned int i;
    unsigned int false_positives = 0, true_positives = 0;
    unsigned int false_negatives = 0, true_negatives = 0;
    bloom_filter *flt;
    flt = create_bfilter(NUM_BUCKETS);

    printf("BINARY: %d\n", BINARY);

    // generate content and insert into filter
    srand((unsigned int)time(NULL));
    for (i = 0; i < NUM_ITEMS; i++)
    {
        randstr(filter_contents[i], STR_LEN);
        bfilter_add(flt, filter_contents[i]);

        // test array with a 50/50 mix of str in filter, and random str
        if (rand() & 1)
            strcpy(test_contents[i], filter_contents[i]);
        else
            randstr(test_contents[i], STR_LEN);
    }

    // test and statistic result
    for (i = 0; i < NUM_ITEMS; i++)
    {
        int filter_present = bfilter_check(flt, test_contents[i]);
        int truely_present = brute_force_search(test_contents[i]);
        if      ( truely_present &&  filter_present) true_positives++;
        else if (!truely_present && !filter_present) true_negatives++;
        else if (!truely_present &&  filter_present) false_positives++;
        else if ( truely_present && !filter_present) false_negatives++;
    }

    printf("NUM_ITEMS: %d\n", NUM_ITEMS);
    printf("True positives: %d\n", true_positives);
    printf("True negatives: %d\n", true_negatives);
	printf("False positives(lower): %d\n", false_positives);
	printf("False negatives(0): %d\n", false_negatives);

    destroy_bfilter(flt);
    return 0;
}
