#ifndef __BLOOMFLT_H__
#define __BLOOMFLT_H__

#define BINARY  1

#if BINARY
typedef unsigned char filter_t;
#else
typedef unsigned int filter_t;
#endif

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
#if !BINARY
void bfilter_del(const bloom_filter* bFilter, const char *key);
#endif

// 字符串hash函数
unsigned int SDBMHash (const char *str);
unsigned int RSHash (const char *str);
unsigned int JSHash (const char *str);
unsigned int PJWHash (const char *str);
unsigned int ELFHash (const char *str);
unsigned int BKDRHash (const char *str);
unsigned int DJBHash (const char *str);
unsigned int APHash (const char *str);

#endif
