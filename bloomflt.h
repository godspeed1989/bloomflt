#ifndef __BLOOMFLT_H__
#define __BLOOMFLT_H__

typedef unsigned int filter_t;

typedef struct _bloom_filter
{
    unsigned long size;
    filter_t* filter;
}bloom_filter;

bloom_filter* create_bfilter(unsigned long size);
void destroy_bfilter(bloom_filter* bFilter);

// ����
void bfilter_add(const bloom_filter* bFilter, const char *key);

// ���
int bfilter_check(const bloom_filter* bFilter, const char *key);

// ɾ��
// !!!ȷ��key�ڼ����в��ܵ���bfilter_del()����!!!
void bfilter_del(const bloom_filter* bFilter, const char *key);

#endif
