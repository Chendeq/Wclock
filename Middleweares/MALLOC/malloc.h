#ifndef __MALLOC_H
#define __MALLOC_H

#include <stdint.h>

/*================= 宏开关：按需打开/关闭内存池 =================*/
#define USE_SRAMIN      1   /* 1-启用内部 SRAM 内存池 */
#define USE_SRAMDTCM    0   /* 1-启用 DTCM 内存池 */
#define USE_SRAMEX      0   /* 1-启用外部 SRAM 内存池 */

/*================= 内存池编号定义 =================*/
#if USE_SRAMIN
#define SRAMIN          0   /* 内部内存池 */
#endif

#if USE_SRAMDTCM
#define SRAMDTCM        1   /* DTCM 内存池 */
#endif

#if USE_SRAMEX
#define SRAMEX          2   /* 外部内存池 */
#endif

/* 实际启用的池数量 */
#define SRAMBANK        (USE_SRAMIN + USE_SRAMDTCM + USE_SRAMEX)

/* 管理表元素类型：32 位位图 */
#define MT_TYPE     uint32_t

/*================= 各池参数配置 =================*/
#if USE_SRAMIN
#define MEM1_BLOCK_SIZE         32      /* 块大小 32 字节 */
#define MEM1_MAX_SIZE           (16 * 1024)                 /* 总容量 16 KB */
#define MEM1_ALLOC_TABLE_SIZE   (MEM1_MAX_SIZE / MEM1_BLOCK_SIZE)   /* 管理表长度 */
#else
#define MEM1_MAX_SIZE           0
#define MEM1_ALLOC_TABLE_SIZE   0
#endif

#if USE_SRAMDTCM
#define MEM2_BLOCK_SIZE         32
#define MEM2_MAX_SIZE           (16 * 1024)
#define MEM2_ALLOC_TABLE_SIZE   (MEM2_MAX_SIZE / MEM2_BLOCK_SIZE)
#else
#define MEM2_MAX_SIZE           0
#define MEM2_ALLOC_TABLE_SIZE   0
#endif

#if USE_SRAMEX
#define MEM3_BLOCK_SIZE         32
#define MEM3_MAX_SIZE           (64 * 1024)
#define MEM3_ALLOC_TABLE_SIZE   (MEM3_MAX_SIZE / MEM3_BLOCK_SIZE)
#else
#define MEM3_MAX_SIZE           0
#define MEM3_ALLOC_TABLE_SIZE   0
#endif

#ifndef NULL
#define NULL 0
#endif

/*================= 内存管理设备结构体 =================*/
struct _m_mallco_dev
{
    void (*init)(uint8_t);              /* 初始化函数 */
    uint16_t (*perused)(uint8_t);       /* 使用率查询函数 */
    uint8_t *membase[SRAMBANK];         /* 内存池起始地址 */
    MT_TYPE *memmap[SRAMBANK];          /* 内存管理表（位图） */
    uint8_t  memrdy[SRAMBANK];          /* 内存池就绪标志 */
};

/* 全局设备实例 */
extern struct _m_mallco_dev mallco_dev;

/*================= 用户接口 =================*/
void my_mem_init(uint8_t memx);         /* 初始化指定池 */
uint16_t my_mem_perused(uint8_t memx);  /* 查询使用率（‰） */
void my_mem_set(void *s, uint8_t c, uint32_t count);  /* 内存置值 */
void my_mem_copy(void *des, void *src, uint32_t n);   /* 内存拷贝 */
void myfree(uint8_t memx, void *ptr);   /* 释放内存 */
void *mymalloc(uint8_t memx, uint32_t size);    /* 申请内存 */
void *myrealloc(uint8_t memx, void *ptr, uint32_t size); /* 重新分配 */
void test_malloc(void);                 /* 测试用例：串口打印使用率 */

#endif
