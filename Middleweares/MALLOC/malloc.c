#include "stm32f4xx.h"
#include "malloc.h"
#include <string.h>
#include "Usart1.h"

/*================= 内存池（64 字节对齐） =================*/
#if USE_SRAMIN
static __align(64) uint8_t mem1base[MEM1_MAX_SIZE];                                     /* 内部 SRAM 内存池 */
#endif

#if USE_SRAMDTCM
static __align(64) uint8_t mem2base[MEM2_MAX_SIZE] __attribute__((at(0x10000000)));     /* DTCM 内存池 */
#endif

#if USE_SRAMEX
static __align(64) uint8_t mem3base[MEM3_MAX_SIZE] __attribute__((at(0x68000000)));     /* 外部 SRAM 内存池 */
#endif

/*================= 内存管理表 =================*/
#if USE_SRAMIN
static MT_TYPE mem1mapbase[MEM1_ALLOC_TABLE_SIZE];                                      /* 内部 SRAM 内存管理表 */
#endif

#if USE_SRAMDTCM
static MT_TYPE mem2mapbase[MEM2_ALLOC_TABLE_SIZE] __attribute__((at(0x10000000 + MEM2_MAX_SIZE)));  /* DTCM 管理表 */
#endif

#if USE_SRAMEX
static MT_TYPE mem3mapbase[MEM3_ALLOC_TABLE_SIZE] __attribute__((at(0x68000000 + MEM3_MAX_SIZE)));  /* 外部 SRAM 管理表 */
#endif

/*================= 内存池容量/块大小/管理表长度常量 =================*/
const uint32_t memtblsize[SRAMBANK] = {             // 内存表大小
#if USE_SRAMIN
    MEM1_ALLOC_TABLE_SIZE,
#endif
#if USE_SRAMDTCM
    MEM2_ALLOC_TABLE_SIZE,
#endif
#if USE_SRAMEX
    MEM3_ALLOC_TABLE_SIZE
#endif
};

const uint32_t memblksize[SRAMBANK] = {             // 内存块大小
#if USE_SRAMIN
    MEM1_BLOCK_SIZE,
#endif
#if USE_SRAMDTCM
    MEM2_BLOCK_SIZE,
#endif
#if USE_SRAMEX
    MEM3_BLOCK_SIZE
#endif
};

const uint32_t memsize[SRAMBANK] = {             // 内存池总大小
#if USE_SRAMIN
    MEM1_MAX_SIZE,
#endif
#if USE_SRAMDTCM
    MEM2_MAX_SIZE,
#endif
#if USE_SRAMEX
    MEM3_MAX_SIZE
#endif
};

/*================= 内存管理设备结构体 =================*/
struct _m_mallco_dev mallco_dev =
{
    my_mem_init,        /* 初始化函数 */
    my_mem_perused,     /* 使用率统计函数 */
    {
#if USE_SRAMIN
        mem1base,       /* 内部 SRAM 池 */
#endif
#if USE_SRAMDTCM
        mem2base,       /* DTCM 池 */
#endif
#if USE_SRAMEX
        mem3base        /* 外部 SRAM 池 */
#endif
    },
    {
#if USE_SRAMIN
        mem1mapbase,    /* 内部 SRAM 管理表 */
#endif
#if USE_SRAMDTCM
        mem2mapbase,    /* DTCM 管理表 */
#endif
#if USE_SRAMEX
        mem3mapbase     /* 外部 SRAM 管理表 */
#endif
    },
#if SRAMBANK == 1
    {0}
#elif SRAMBANK == 2
    {0, 0}
#elif SRAMBANK == 3
    {0, 0, 0}
#else
    {}  /* SRAMBANK 为 0 时为空 */
#endif
};

/**
 * @brief  内存拷贝（memcpy 简易实现）
 */
void my_mem_copy(void *des, void *src, uint32_t n)
{
    uint8_t *xdes = des;
    uint8_t *xsrc = src;
    while (n--) *xdes++ = *xsrc++;
}

/**
 * @brief  内存置值（memset 简易实现）
 */
void my_mem_set(void *s, uint8_t c, uint32_t count)
{
    uint8_t *xs = s;
    while (count--) *xs++ = c;
}

/**
 * @brief  初始化指定内存池的管理表
 * @param  memx：内存池编号（SRAMIN / SRAMDTCM / SRAMEX）
 */
void my_mem_init(uint8_t memx)
{
    if (memx >= SRAMBANK) return;

    uint8_t mttsize = sizeof(MT_TYPE);
    /* 清空管理表 = 全部块标记为“空闲” */
    my_mem_set(mallco_dev.memmap[memx], 0, memtblsize[memx] * mttsize);
    mallco_dev.memrdy[memx] = 1;        /* 标记当前池已就绪 */
}

/**
 * @brief  计算并返回内存池使用率（‰）
 * @param  memx：内存池编号
 * @retval 使用率 ‰（千分比）
 */
uint16_t my_mem_perused(uint8_t memx)
{
    if (memx >= SRAMBANK) return 0;

    uint32_t used = 0;
    uint32_t i;
    for (i = 0; i < memtblsize[memx]; i++)
    {
        if (mallco_dev.memmap[memx][i]) used++;
    }
    return (used * 1000) / (memtblsize[memx]);   /* ‰ 精度 */
}

/**
 * @brief  内存分配（内部实现，返回偏移地址）
 * @param  memx：内存池编号
 * @param  size：用户请求字节数
 * @retval 成功返回偏移地址；失败返回 0xFFFFFFFF
 */
static uint32_t my_mem_malloc(uint8_t memx, uint32_t size)
{
    if (memx >= SRAMBANK) return 0xFFFFFFFF;

    signed long offset = 0;
    uint32_t nmemb;     /* 所需块数 */
    uint32_t cmemb = 0; /* 连续空闲块计数 */
    uint32_t i;

    /* 若未初始化，先初始化 */
    if (!mallco_dev.memrdy[memx])
    {
        mallco_dev.init(memx);
    }

    if (size == 0) return 0xFFFFFFFF;

    /* 计算所需块数（向上取整） */
    nmemb = size / memblksize[memx];
    if (size % memblksize[memx]) nmemb++;

    /* 从后往前扫描管理表，找“连续空闲块” */
    for (offset = memtblsize[memx] - 1; offset >= 0; offset--)
    {
        if (!mallco_dev.memmap[memx][offset])
            cmemb++;                /* 当前块空闲，计数++ */
        else
            cmemb = 0;              /* 遇到占用块，清零 */

        if (cmemb == nmemb)         /* 找到合适连续块 */
        {
            for (i = 0; i < nmemb; i++)
                mallco_dev.memmap[memx][offset + i] = nmemb; /* 标记占用 */
            return (offset * memblksize[memx]);              /* 返回偏移 */
        }
    }
    return 0xFFFFFFFF;              /* 无足够空间 */
}

/**
 * @brief  内存释放（内部实现）
 * @param  memx：内存池编号
 * @param  offset：相对池首地址的偏移
 * @retval 0 成功；1 未初始化；2 偏移非法
 */
static uint8_t my_mem_free(uint8_t memx, uint32_t offset)
{
    if (memx >= SRAMBANK) return 2;

    int i;
    if (!mallco_dev.memrdy[memx])       /* 未初始化 */
    {
        mallco_dev.init(memx);
        return 1;
    }

    if (offset < memsize[memx])         /* 偏移合法 */
    {
        int index = offset / memblksize[memx];
        int nmemb = mallco_dev.memmap[memx][index]; /* 块数 */
        for (i = 0; i < nmemb; i++)
            mallco_dev.memmap[memx][index + i] = 0; /* 全部清 0 = 空闲 */
        return 0;
    }
    else
    {
        return 2;   /* 偏移越界 */
    }
}

/**
 * @brief  用户层释放内存
 * @param  memx：内存池编号
 * @param  ptr：my_malloc/mymalloc 返回的指针
 */
void myfree(uint8_t memx, void *ptr)
{
    if (memx >= SRAMBANK || ptr == NULL) return;

    uint32_t offset = (uint32_t)ptr - (uint32_t)mallco_dev.membase[memx];
    my_mem_free(memx, offset);
}

/**
 * @brief  用户层申请内存
 * @param  memx：内存池编号
 * @param  size：字节数
 * @retval 成功返回指针；失败返回 NULL
 */
void *mymalloc(uint8_t memx, uint32_t size)
{
    if (memx >= SRAMBANK) return NULL;

    uint32_t offset = my_mem_malloc(memx, size);
    if (offset == 0xFFFFFFFF)
        return NULL;
    else
        return (void *)((uint32_t)mallco_dev.membase[memx] + offset);
}

/**
 * @brief  用户层重新分配内存（先申请新块，再拷贝，再释放旧块）
 * @param  memx：内存池编号
 * @param  ptr：旧指针
 * @param  size：新尺寸
 * @retval 成功返回新指针；失败返回 NULL
 */
void *myrealloc(uint8_t memx, void *ptr, uint32_t size)
{
    if (memx >= SRAMBANK) return NULL;

    uint32_t offset = my_mem_malloc(memx, size);
    if (offset == 0xFFFFFFFF)
        return NULL;

    my_mem_copy((void *)((uint32_t)mallco_dev.membase[memx] + offset), ptr, size);
    myfree(memx, ptr);      /* 释放旧块 */
    return (void *)((uint32_t)mallco_dev.membase[memx] + offset);
}

/**
 * @brief  内存管理测试函数（串口打印使用率）
 */
void test_malloc(void)
{
    Serial_Printf("Memory Management Test - %d banks enabled\r\n", SRAMBANK);

#if USE_SRAMIN
    uint8_t *p1 = mymalloc(SRAMIN, 1000);
    if (p1)
    {
        Serial_Printf("SRAMIN allocation successful! Usage: %d%%\r\n", my_mem_perused(SRAMIN) / 10);
        myfree(SRAMIN, p1);
        Serial_Printf("SRAMIN Memory freed successfully!\r\n");
    }
#endif

#if USE_SRAMDTCM
    uint8_t *p2 = mymalloc(SRAMDTCM, 1000);
    if (p2)
    {
        Serial_Printf("SRAMDTCM allocation successful! Usage: %d%%\r\n", my_mem_perused(SRAMDTCM) / 10);
        myfree(SRAMDTCM, p2);
        Serial_Printf("SRAMDTCM Memory freed successfully!\r\n");
    }
#endif

#if USE_SRAMEX
    uint8_t *p3 = mymalloc(SRAMEX, 3300);
    if (p3)
    {
        Serial_Printf("SRAMEX allocation successful! Usage: %d%%\r\n", my_mem_perused(SRAMEX) / 10);
        myfree(SRAMEX, p3);
        Serial_Printf("SRAMEX Memory freed successfully!\r\n");
    }
#endif
}
