#include "fonts.h"
#include "ff.h"
#include "w25q128.h"

/*------------------------------------------------------------------------*/
/* 静态码页配置下的 OEM <==> Unicode 互转函数（DBCS 固定码页）            */
/*------------------------------------------------------------------------*/

/**
 * @brief  Unicode → OEM 编码
 * @param  uni: UTF-16 字符
 * @param  cp: 码页（未使用，固定 GBK）
 * @retval 转换后的 OEM 字符；失败返回 0
 */
WCHAR ff_uni2oem(
    DWORD   uni,    /* 待转换的 UTF-16 字符 */
    WORD    cp)     /* 码页（本实现固定 GBK） */
{
    WCHAR t[2];
    WCHAR c;
    uint32_t i, li, hi;
    uint16_t n;
    uint32_t gbk2uni_offset = 0;

    /* ASCII 直接返回 */
    if (uni < 0x80)
    {
        c = uni;
    }
    else
    {
        /* 二分法查表：在 Flash 中查找 Unicode→GBK 映射 */
        hi = ftinfo.ugbksize / 2;   /* 映射表总条目数 */
        hi = hi / 4 - 1;
        li = 0;

        for (n = 16; n; n--)        /* 最多 16 次折半 */
        {
            i = li + (hi - li) / 2;
            /* 从 W25Q128 读 4 字节：Unicode + GBK */
            norflash_read((uint8_t *)&t, ftinfo.ugbkaddr + i * 4 + gbk2uni_offset, 4);

            if (uni == t[0]) break; /* 找到对应 Unicode */

            if (uni > t[0])
                li = i;
            else
                hi = i;
        }

        c = n ? t[1] : 0;           /* 成功则返回 GBK，否则 0 */
    }

    return c;
}

/**
 * @brief  OEM → Unicode 编码
 * @param  oem: OEM 字符（GBK）
 * @param  cp: 码页（未使用）
 * @retval 转换后的 Unicode；失败返回 0
 */
WCHAR ff_oem2uni(
    WCHAR   oem,    /* 待转换的 GBK 字符 */
    WORD    cp)     /* 码页（固定 GBK） */
{
    WCHAR t[2];
    WCHAR c;
    uint32_t i, li, hi;
    uint16_t n;
    /* 后半个表：GBK→Unicode */
    uint32_t gbk2uni_offset = ftinfo.ugbksize / 2;

    /* ASCII 直接返回 */
    if (oem < 0x80)
    {
        c = oem;
    }
    else
    {
        hi = ftinfo.ugbksize / 2;
        hi = hi / 4 - 1;
        li = 0;

        for (n = 16; n; n--)        /* 二分查找 */
        {
            i = li + (hi - li) / 2;
            norflash_read((uint8_t *)&t, ftinfo.ugbkaddr + i * 4 + gbk2uni_offset, 4);

            if (oem == t[0]) break; /* 找到对应 GBK */

            if (oem > t[0])
                li = i;
            else
                hi = i;
        }

        c = n ? t[1] : 0;           /* 成功返回 Unicode，否则 0 */
    }

    return c;
}

/*------------------------------------------------------------------------*/
/* Unicode 转大写函数（仅 BMP 内字符）                                     */
/*------------------------------------------------------------------------*/

DWORD ff_wtoupper(
    DWORD uni)      /* 待转大写的 Unicode 码位 */
{
    const WORD *p;
    WORD uc, bc, nc, cmd;

    /* 压缩表：U+0000 - U+0FFF */
    static const WORD cvt1[] = {
        /* 基本拉丁、拉丁-1 补充、拉丁扩展-A/B ... */
        0x0061, 0x031A,
        0x00E0, 0x0317,
        0x00F8, 0x0307,
        0x00FF, 0x0001, 0x0178,
        /* ... 原表数据过长，此处省略，与源码一致 ... */
        0x0000      /* 表结束 */
    };

    /* 压缩表：U+1000 - U+FFFF */
    static const WORD cvt2[] = {
        /* 音标扩展、希腊、科普特、西里尔、亚美尼亚 ... */
        0x1D7D, 0x0001, 0x2C63,
        0x1E00, 0x0196,
        0x1EA0, 0x015A,
        /* ... 原表数据过长，此处省略，与源码一致 ... */
        0x0000      /* 表结束 */
    };

    if (uni < 0x10000)          /* 仅在 BMP 内转换 */
    {
        uc = (WORD)uni;
        p  = (uc < 0x1000) ? cvt1 : cvt2;

        for (;;)
        {
            bc = *p++;                  /* 块起始码位 */
            if (bc == 0 || uc < bc)     /* 未匹配 */
                break;

            nc  = *p++;
            cmd = nc >> 8;              /* 高 8 位：命令 */
            nc &= 0xFF;                 /* 低 8 位：块长度 */

            if (uc < bc + nc)           /* 落在当前块 */
            {
                switch (cmd)
                {
                case 0:  uc = p[uc - bc]; break;   /* 查表映射 */
                case 1:  uc -= (uc - bc) & 1; break; /* 大小写成对 */
                case 2:  uc -= 16; break;            /* 偏移 -16 */
                case 3:  uc -= 32; break;            /* 偏移 -32 */
                case 4:  uc -= 48; break;            /* 偏移 -48 */
                case 5:  uc -= 26; break;            /* 偏移 -26 */
                case 6:  uc += 8; break;             /* 偏移 +8 */
                case 7:  uc -= 80; break;            /* 偏移 -80 */
                case 8:  uc -= 0x1C60; break;        /* 偏移 -0x1C60 */
                }
                break;
            }

            if (cmd == 0)
                p += nc;            /* 跳过当前整块表 */
        }

        uni = uc;
    }

    return uni;                     /* 返回大写后的码位 */
}
