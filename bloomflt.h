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

// ����
void bfilter_add(const bloom_filter* bFilter, const char *key);

// ���
int bfilter_check(const bloom_filter* bFilter, const char *key);

// ɾ��
// !!!ȷ��key�ڼ����в��ܵ���bfilter_del()����!!!
#if !BINARY
void bfilter_del(const bloom_filter* bFilter, const char *key);
#endif

// �ַ���hash����
unsigned int SDBMHash (const char *str);
unsigned int RSHash (const char *str);
unsigned int JSHash (const char *str);
unsigned int PJWHash (const char *str);
unsigned int ELFHash (const char *str);
unsigned int BKDRHash (const char *str);
unsigned int DJBHash (const char *str);
unsigned int APHash (const char *str);

#endif
