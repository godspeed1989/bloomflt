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

// 加入
void bfilter_add(const bloom_filter* bFilter, const char *key);

// 检测
int bfilter_check(const bloom_filter* bFilter, const char *key);

// 删除
// !!!确认key在集合中才能调用bfilter_del()函数!!!
void bfilter_del(const bloom_filter* bFilter, const char *key);

#endif
