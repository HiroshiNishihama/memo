#include "c6x.h"
#include "limits.h"
#include "string.h"

int _abs(int src)
{
    int dst;
    if (src > 0)
    {
        dst = src;
    }
    else if (src != 0x80000000)
    {
        dst = -src;
    }
    else
    {
        dst = 0x80000000 - 1;
    }

    return dst;
}

__int40_t _labs(__int40_t src)
{
    __int40_t dst;
    if (src > 0)
    {
        dst = src;
    }
    else if (src != 0x8000000000000000LL)
    {
        dst = -src;
    }
    else
    {
        dst = 0x8000000000000000LL - 1;
    }

    return dst;
}

int _abs2(int src)
{
    int dst;
    int lsb16, msb16;
    lsb16 = _extr(src, (16 << 5) + 16);
    msb16 = _extr(src, 16);
    lsb16 = _abs(lsb16);
    msb16 = _abs(msb16);
    if (lsb16 > 0x7fff)
    {
        lsb16 = 0x7fff;
    }
    if (msb16 > 0x7fff)
    {
        msb16 = 0x7fff;
    }
    dst = ((msb16 << 16) & 0xffff0000) | (lsb16 & 0x0000ffff);
    return dst;
}

int _add2(int src1, int src2)
{
    int lsb16, msb16;
    int cst_lsb = (16 << 5) + 16;
    int cst_msb = 16;
    int dst;

    lsb16 = _extr(src1, cst_lsb) + _extr(src2, cst_lsb);
    msb16 = _extr(src1, cst_msb) + _extr(src2, cst_msb);
    dst = ((msb16 << 16) & 0xffff0000) | (lsb16 & 0x0000ffff);
    return dst;
}

long long _addsub(int src1, int src2)
{
    long long dst;
    dst = ((long long)(src1 + src2) << 32) & 0xFFFFFFFF00000000LL;
    dst |= (long long)(src1 - src2) & 0x00000000FFFFFFFFLL;
    return dst;
}

long long _addsub2(int src1, int src2)
{
    long long dst;
    int dst_o, dst_e;
    int tmp1, tmp2;
    tmp1 = _extr(src1, 16) + _extr(src2, 16);                         // msb16(src1) + msb16(src2)
    tmp2 = _extr(src1, (16 << 5) + 16) + _extr(src2, (16 << 5) + 16); // lsb16(src) + lsb16(src2)
    dst_o = ((tmp1 << 16) & 0xFFFF0000) | (tmp2 & 0x0000FFFF);
    tmp1 = _extr(src1, 16) - _extr(src2, 16);                         // msb16(src1) - msb16(src2)
    tmp2 = _extr(src1, (16 << 5) + 16) - _extr(src2, (16 << 5) + 16); // lsb16(src) - lsb16(src2)
    dst_e = ((tmp1 << 16) & 0xFFFF0000) | (tmp2 & 0x0000FFFF);
    dst = (((long long)dst_o << 32) & 0xFFFFFFFF00000000LL) | ((long long)dst_e & 0x00000000FFFFFFFFLL);
    return dst;
}

int _add4(int src1, int src2)
{
    int a0, a1, a2, a3;
    int b0, b1, b2, b3;
    int dst;

    a0 = _extr(src1, (24 << 5) + 24);
    a1 = _extr(src1, (16 << 5) + 24);
    a2 = _extr(src1, (8 << 5) + 24);
    a3 = _extr(src1, 24);
    b0 = _extr(src2, (24 << 5) + 24);
    b1 = _extr(src2, (16 << 5) + 24);
    b2 = _extr(src2, (8 << 5) + 24);
    b3 = _extr(src2, 24);

    dst = ((a3 + b3) << 24) & 0xFF000000;
    dst |= ((a2 + b2) << 16) & 0x00FF0000;
    dst |= ((a1 + b1) << 8) & 0x0000FF00;
    dst |= ((a0 + b0)) & 0x000000FF;
    return dst;
}

int _avg2(int src1, int src2)
{
    int dst;
    int lsb16, msb16;
    lsb16 = _extr(src1, (16 << 5) + 16) + _extr(src2, (16 << 5) + 16) + 1;
    lsb16 = lsb16 >> 1;

    msb16 = _extr(src1, 16) + _extr(src2, 16) + 1;
    msb16 = msb16 >> 1;

    dst = (msb16 << 16) & 0xFFFF0000;
    dst |= lsb16 & 0x0000FFFF;
    return dst;
}

unsigned int _avgu4(unsigned int src1, unsigned int src2)
{
    unsigned int dst;
    unsigned int ua0, ua1, ua2, ua3;
    ua0 = _extu(src1, 24, 24) + _extu(src2, 24, 24) + 1;
    ua0 = ua0 >> 1;

    ua1 = _extu(src1, 16, 24) + _extu(src2, 16, 24) + 1;
    ua1 = ua1 >> 1;

    ua2 = _extu(src1, 8, 24) + _extu(src2, 8, 24) + 1;
    ua2 = ua2 >> 1;

    ua3 = _extu(src1, 0, 24) + _extu(src2, 0, 24) + 1;
    ua3 = ua3 >> 1;

    dst = (ua3 << 24) | (ua2 << 16) | (ua1 << 8) | ua0;
    return dst;
}

static unsigned int __bitc32(unsigned int src)
{
    int i;
    unsigned bit_count = 0;
    unsigned int mask;
    for (i = 0; i < 32; i++)
    {
        mask = 0x01 << i;
        if ((mask & src) == mask)
        {
            bit_count += 1;
        }
    }
    return bit_count;
}

unsigned int _bitc4(unsigned int src)
{
    unsigned int dst = 0;
    unsigned int bit_count;
    bit_count = __bitc32(_extu(src, 0, 24));
    dst = bit_count << 24;
    bit_count = __bitc32(_extu(src, 8, 24));
    dst |= bit_count << 16;
    bit_count = __bitc32(_extu(src, 16, 24));
    dst |= bit_count << 8;
    bit_count = __bitc32(_extu(src, 24, 24));
    dst |= bit_count;
    return dst;
}

unsigned int _bitr(unsigned int src)
{
    unsigned int dst = 0;
    unsigned int bit;
    int i;
    for (i = 0; i < 32; i++)
    {
        bit = _extu(src, i, 31);
        dst |= _extu(bit, i, 0);
    }
    return dst;
}

int _ext(int src2, unsigned csta, unsigned cstb)
{
    int dst;

    dst = src2 << csta;
    dst = dst >> cstb;
    return dst;
}

int _extr(int src2, int src1)
{
    unsigned int csta, cstb;
    int dst;

    csta = (src1 >> 5) & 0x1f;
    cstb = src1 & 0x1f;
    dst = src2 << csta;
    dst = dst >> cstb;
    return dst;
}

unsigned int _clr(unsigned int src2, unsigned int csta, unsigned int cstb)
{
    unsigned int dst;
    unsigned int mask;
    unsigned int n;
    n = 31 - cstb;
    mask = _extu(0xFFFFFFFF, n, n + csta) << csta;
    mask = ~mask;
    dst = src2 & mask;
    return dst;
}

unsigned int _clrr(unsigned int src2, int src1)
{
    unsigned int dst;
    unsigned int csta, cstb;
    csta = (src1 >> 5) & 0x1f;
    cstb = src1 & 0x1f;
    dst = _clr(src2, csta, cstb);
    return dst;
}

unsigned int _extu(unsigned int src2, unsigned int csta, unsigned int cstb)
{
    unsigned int dst;

    dst = src2 << csta;
    dst = dst >> cstb;
    return dst;
}

unsigned int _extur(unsigned int src2, int src1)
{
    unsigned int csta, cstb;
    unsigned int dst;

    csta = (src1 >> 5) & 0x1f;
    cstb = src1 & 0x1f;
    dst = _extu(src2, csta, cstb);
    return dst;
}

int _cmpeq2(int src1, int src2)
{
    int dst = 0;
    int a, b;

    /* MSB16 */
    a = _extr(src1, 16);
    b = _extr(src2, 16);
    if (a == b)
    {
        dst |= 0x02;
    }
    /* LSB16 */
    a = _extr(src1, (16 << 5) + 16);
    b = _extr(src2, (16 << 5) + 16);
    if (a == b)
    {
        dst |= 0x01;
    }
    return dst;
}

int _cmpeq4(int src1, int src2)
{
    int dst = 0;
    int a, b;
    a = _extr(src1, 24);
    b = _extr(src2, 24);
    if (a == b)
    {
        dst |= 0x08;
    }
    a = _extr(src1, (8 << 5) + 24);
    b = _extr(src2, (8 << 5) + 24);
    if (a == b)
    {
        dst |= 0x04;
    }
    a = _extr(src1, (16 << 5) + 24);
    b = _extr(src2, (16 << 5) + 24);
    if (a == b)
    {
        dst |= 0x02;
    }
    a = _extr(src1, (24 << 5) + 24);
    b = _extr(src2, (24 << 5) + 24);
    if (a == b)
    {
        dst |= 0x01;
    }
    return dst;
}

int _cmpgt2(int src1, int src2)
{
    int dst = 0;
    int a, b;

    /* MSB16 */
    a = _extr(src1, 16);
    b = _extr(src2, 16);
    if (a > b)
    {
        dst |= 0x02;
    }
    /* LSB16 */
    a = _extr(src1, (16 << 5) + 16);
    b = _extr(src2, (16 << 5) + 16);
    if (a > b)
    {
        dst |= 0x01;
    }
    return dst;
}
unsigned _cmpgtu4(unsigned src1, unsigned src2)
{
    unsigned int dst = 0;
    unsigned int a, b;
    a = _extur(src1, 24);
    b = _extur(src2, 24);
    if (a > b)
    {
        dst |= 0x08;
    }
    a = _extur(src1, (8 << 5) + 24);
    b = _extur(src2, (8 << 5) + 24);
    if (a > b)
    {
        dst |= 0x04;
    }
    a = _extur(src1, (16 << 5) + 24);
    b = _extur(src2, (16 << 5) + 24);
    if (a > b)
    {
        dst |= 0x02;
    }
    a = _extur(src1, (24 << 5) + 24);
    b = _extur(src2, (24 << 5) + 24);
    if (a > b)
    {
        dst |= 0x01;
    }
    return dst;
}

int _cmplt2(int src1, int src2)
{
    int dst = 0;
    int a, b;

    /* MSB16 */
    a = _extr(src1, 16);
    b = _extr(src2, 16);
    if (a < b)
    {
        dst |= 0x02;
    }
    /* LSB16 */
    a = _extr(src1, (16 << 5) + 16);
    b = _extr(src2, (16 << 5) + 16);
    if (a < b)
    {
        dst |= 0x01;
    }
    return dst;
}

unsigned _cmpltu4(unsigned src1, unsigned src2)
{
    unsigned int dst = 0;
    unsigned int a, b;
    a = _extur(src1, 24);
    b = _extur(src2, 24);
    if (a < b)
    {
        dst |= 0x08;
    }
    a = _extur(src1, (8 << 5) + 24);
    b = _extur(src2, (8 << 5) + 24);
    if (a < b)
    {
        dst |= 0x04;
    }
    a = _extur(src1, (16 << 5) + 24);
    b = _extur(src2, (16 << 5) + 24);
    if (a < b)
    {
        dst |= 0x02;
    }
    a = _extur(src1, (24 << 5) + 24);
    b = _extur(src2, (24 << 5) + 24);
    if (a < b)
    {
        dst |= 0x01;
    }
    return dst;
}

int _sadd(int src1, int src2)
{
    int result;
    result = src1 + src2;
    if (((src1 > 0) && (src2 > 0)) && (unsigned int)result >= (unsigned int)INT_MAX)
    {
        result = INT_MAX;
    }
    if (((src1 < 0) && (src2 < 0)) && (unsigned int)result <= (unsigned int)INT_MIN)
    {
        result = INT_MIN;
    }
    return result;
}

long long _cmpy(unsigned src1, unsigned src2)
{
    long long dst = 0LL;
    int real;
    int im;
    int r1, r2;
    int i1, i2;

    r1 = _extr(src1, 16);
    r2 = _extr(src2, 16);
    i1 = _extr(src1, (16 << 5) + 16);
    i2 = _extr(src2, (16 << 5) + 16);
    real = (r1 * r2) - (i1 * i2);
    // overflow case
    if ((src1 == 0x80008000) && (src2 == 0x80008000))
    {
        im = 0x7fffffffLL;
    }
    else
    {
        im = (i1 * r2) + (r1 * i2);
    }
    dst = ((long long)real << 32) & 0xFFFFFFFF00000000LL;
    dst |= (long long)im & 0x00000000FFFFFFFFLL;
    return dst;
}

unsigned _cmpyr(unsigned src1, unsigned src2)
{
    unsigned int dst;
    int tmp_e, tmp_o;
    int r1, r2;
    int i1, i2;
    r1 = _extr(src1, 16);
    r2 = _extr(src2, 16);
    i1 = _extr(src1, (16 << 5) + 16);
    i2 = _extr(src2, (16 << 5) + 16);
    tmp_o = _sadd((r1 * r2), -(i1 * i2));
    tmp_o = _sadd(tmp_o, 0x00008000);
    tmp_o = _extu(tmp_o, 0, 16);
    tmp_e = _sadd((i1 * r2), (r1 * i2));
    tmp_e = _sadd(tmp_e, 0x00008000);
    tmp_e = _extu(tmp_e, 0, 16);
    dst = (tmp_o << 16) & 0xFFFF0000;
    dst |= tmp_e & 0x0000FFFF;
    return dst;
}

unsigned _cmpyr1(unsigned src1, unsigned src2)
{
    unsigned int dst;
    int tmp_e, tmp_o;
    int r1, r2;
    int i1, i2;
    r1 = _extr(src1, 16);
    r2 = _extr(src2, 16);
    i1 = _extr(src1, (16 << 5) + 16);
    i2 = _extr(src2, (16 << 5) + 16);
    tmp_o = _sadd((r1 * r2), -(i1 * i2));
    tmp_o = _sadd(tmp_o, 0x00004000);
    tmp_o = _sadd(tmp_o, tmp_o); // sat(tmp_o << 1)
    tmp_o = _extu(tmp_o, 0, 16);
    tmp_e = _sadd((i1 * r2), (r1 * i2));
    tmp_e = _sadd(tmp_e, 0x00004000);
    tmp_e = _sadd(tmp_e, tmp_e); // sat(tmp_e << 1)
    tmp_e = _extu(tmp_e, 0, 16);
    dst = (tmp_o << 16) & 0xFFFF0000;
    dst |= tmp_e & 0x0000FFFF;
    return dst;
}

long long _ddotp4(unsigned src1, unsigned src2)
{
    long long dst;
    int dst_e, dst_o;
    int d0, d1;
    int c0, c1, c2, c3;

    d0 = _extr(src1, (16 << 5) + 16);
    d1 = _extr(src1, 16);
    c0 = _extr(src2, (24 << 5) + 24);
    c1 = _extr(src2, (16 << 5) + 24);
    c2 = _extr(src2, (8 << 5) + 24);
    c3 = _extr(src2, 24);
    dst_e = (d1 * c1) + (d0 * c0);
    dst_o = (d1 * c3) + (d0 * c2);
    dst = ((long long)dst_o << 32) & 0xFFFFFFFF00000000LL;
    dst |= (long long)dst_e & 0x00000000FFFFFFFFLL;
    return dst;
}

long long _ddotph2(long long src1, unsigned src2)
{
    long long dst;
    int dst_e, dst_o;
    int d0, d1, d2, d3;
    int c0, c1;
    int src1_e, src1_o;

    src1_o = (int)(src1 >> 32);
    src1_e = (int)(src1 & 0xFFFFFFFF);
    d0 = _extr(src1_e, (16 << 5) + 16);
    d1 = _extr(src1_e, 16);
    d2 = _extr(src1_o, (16 << 5) + 16);
    d3 = _extr(src1_o, 16);
    c0 = _extr(src2, (16 << 5) + 16);
    c1 = _extr(src2, 16);
    dst_o = _sadd((d3 * c1), (d2 * c0));
    dst_e = _sadd((d2 * c1), (d1 * c0));
    dst = ((long long)dst_o << 32) & 0xFFFFFFFF00000000LL;
    dst |= (long long)dst_e & 0x00000000FFFFFFFFLL;
    return dst;
}

long long _ddotpl2(long long src1, unsigned src2)
{
    long long dst;
    int dst_e, dst_o;
    int d0, d1, d2, d3;
    int c0, c1;
    int src1_e, src1_o;

    src1_o = (int)(src1 >> 32);
    src1_e = (int)(src1 & 0xFFFFFFFF);
    d0 = _extr(src1_e, (16 << 5) + 16);
    d1 = _extr(src1_e, 16);
    d2 = _extr(src1_o, (16 << 5) + 16);
    d3 = _extr(src1_o, 16);
    c0 = _extr(src2, (16 << 5) + 16);
    c1 = _extr(src2, 16);
    dst_o = _sadd((d2 * c1), (d1 * c0));
    dst_e = _sadd((d1 * c1), (d0 * c0));
    dst = ((long long)dst_o << 32) & 0xFFFFFFFF00000000LL;
    dst |= (long long)dst_e & 0x00000000FFFFFFFFLL;
    return dst;
}

unsigned _ddotph2r(long long src1, unsigned src2)
{
    unsigned int dst;
    int lsb16, msb16;
    int src1_e, src1_o;
    int d0, d1, d2, d3;
    int c0, c1;

    src1_o = (int)(src1 >> 32);
    src1_e = (int)(src1 & 0xFFFFFFFF);
    d0 = _extr(src1_e, (16 << 5) + 16); // lsb16(src1_e)
    d1 = _extr(src1_e, 16);             // msb16(src1_e)
    d2 = _extr(src1_o, (16 << 5) + 16); // lsb16(src1_o)
    d3 = _extr(src1_o, 16);             // msb16(src1_o)
    c0 = _extr(src2, (16 << 5) + 16);   // lsb16(src2)
    c1 = _extr(src2, 16);               // msb16(src2)
    lsb16 = _sadd((d2 * c1), (d1 * c0));
    lsb16 = _sadd(lsb16, 0x8000);
    msb16 = _sadd((d3 * c1), (d2 * c0));
    msb16 = _sadd(msb16, 0x8000);
    dst = (_extr(msb16, 16) << 16) & 0xFFFF0000;
    dst |= _extr(lsb16, 16) & 0x0000FFFF;
    return dst;
}

unsigned _ddotpl2r(long long src1, unsigned src2)
{
    unsigned int dst;
    int lsb16, msb16;
    int src1_e, src1_o;
    int d0, d1, d2, d3;
    int c0, c1;

    src1_o = (int)(src1 >> 32);
    src1_e = (int)(src1 & 0xFFFFFFFF);
    d0 = _extr(src1_e, (16 << 5) + 16); // lsb16(src1_e)
    d1 = _extr(src1_e, 16);             // msb16(src1_e)
    d2 = _extr(src1_o, (16 << 5) + 16); // lsb16(src1_o)
    d3 = _extr(src1_o, 16);             // msb16(src1_o)
    c0 = _extr(src2, (16 << 5) + 16);   // lsb16(src2)
    c1 = _extr(src2, 16);               // msb16(src2)
    lsb16 = _sadd((d1 * c1), (d0 * c0));
    lsb16 = _sadd(lsb16, 0x8000);
    msb16 = _sadd((d2 * c1), (d1 * c0));
    msb16 = _sadd(msb16, 0x8000);
    dst = (_extr(msb16, 16) << 16) & 0xFFFF0000;
    dst |= _extr(lsb16, 16) & 0x0000FFFF;
    return dst;
}

unsigned _deal(unsigned src)
{
    unsigned int dst = 0;
    unsigned int tmp = 0;
    int i;
    tmp = 0;
    for (i = 0; i < 16; i++)
    {
        tmp = _extu(src, 31 - i * 2, 31);
        dst |= tmp << i;
    }
    for (i = 0; i < 16; i++)
    {
        tmp = _extu(src, 31 - i * 2 - 1, 31);
        dst |= tmp << (i + 16);
    }

    return dst;
}

long long _dmv(int src1, int src2)
{
    long long dst = 0;
    dst = ((long long)src1 << 32) & 0xFFFFFFFF00000000;
    dst |= (long long)src2 & 0x00000000FFFFFFFF;
    return dst;
}

int _dotp2(int src1, int src2)
{
    int dst;
    int a_hi, a_lo;
    int b_hi, b_lo;
    a_hi = _extr(src1, 16);
    a_lo = _extr(src1, (16 << 5) + 16);
    b_hi = _extr(src2, 16);
    b_lo = _extr(src2, (16 << 5) + 16);
    dst = (a_hi * b_hi) + (a_lo * b_lo);
    return dst;
}

__int40_t _ldotp2(int src1, int src2)
{
    __int40_t dst;
    int a_hi, a_lo;
    int b_hi, b_lo;
    a_hi = _extr(src1, 16);
    a_lo = _extr(src1, (16 << 5) + 16);
    b_hi = _extr(src2, 16);
    b_lo = _extr(src2, (16 << 5) + 16);
    dst = (a_hi * b_hi) + (a_lo * b_lo);
    return dst;
}

int _dotpn2(int src1, int src2)
{
    int dst;
    int a_hi, a_lo;
    int b_hi, b_lo;
    a_hi = _extr(src1, 16);
    a_lo = _extr(src1, (16 << 5) + 16);
    b_hi = _extr(src2, 16);
    b_lo = _extr(src2, (16 << 5) + 16);
    dst = (a_hi * b_hi) - (a_lo * b_lo);
    return dst;
}

int _dotpnrsu2(int src1, unsigned src2)
{
    int dst;
    int a_hi, a_lo;
    unsigned int b_hi, b_lo;
    a_hi = _extr(src1, 16);
    a_lo = _extr(src1, (16 << 5) + 16);
    b_hi = _extur(src2, 16);
    b_lo = _extur(src2, (16 << 5) + 16);
    dst = (a_hi * b_hi) - (a_lo * b_lo) + 0x8000;
    dst = dst >> 16;
    return dst;
}

int _dotpnrus2(unsigned src1, int src2)
{
    int dst;
    unsigned int a_hi, a_lo;
    int b_hi, b_lo;
    a_hi = _extur(src1, 16);
    a_lo = _extur(src1, (16 << 5) + 16);
    b_hi = _extr(src2, 16);
    b_lo = _extr(src2, (16 << 5) + 16);
    dst = (a_hi * b_hi) - (a_lo * b_lo) + 0x8000;
    dst = dst >> 16;
    return dst;
}

int _dotprsu2(int src1, unsigned src2)
{
    int dst;
    long long int33;
    int a_hi, a_lo;
    unsigned int b_hi, b_lo;
    a_hi = _extr(src1, 16);
    a_lo = _extr(src1, (16 << 5) + 16);
    b_hi = _extur(src2, 16);
    b_lo = _extur(src2, (16 << 5) + 16);
    int33 = ((long long)a_hi * b_hi) + ((long long)a_lo * b_lo) + 0x8000;
    dst = (int)(int33 >> 16);
    return dst;
}

int _dotpsu4(int src1, unsigned src2)
{
    int dst;
    int a0, a1, a2, a3;
    unsigned int b0, b1, b2, b3;
    a0 = _extr(src1, (24 << 5) + 24);
    a1 = _extr(src1, (16 << 5) + 24);
    a2 = _extr(src1, (8 << 5) + 24);
    a3 = _extr(src1, 24);
    b0 = _extur(src2, (24 << 5) + 24);
    b1 = _extur(src2, (16 << 5) + 24);
    b2 = _extur(src2, (8 << 5) + 24);
    b3 = _extur(src2, 24);
    dst = (a0 * b0) + (a1 * b1) + (a2 * b2) + (a3 * b3);
    return dst;
}
int _dotpus4(unsigned src1, int src2)
{
    int dst;
    unsigned int a0, a1, a2, a3;
    int b0, b1, b2, b3;
    a0 = _extur(src1, (24 << 5) + 24);
    a1 = _extur(src1, (16 << 5) + 24);
    a2 = _extur(src1, (8 << 5) + 24);
    a3 = _extur(src1, 24);
    b0 = _extr(src2, (24 << 5) + 24);
    b1 = _extr(src2, (16 << 5) + 24);
    b2 = _extr(src2, (8 << 5) + 24);
    b3 = _extr(src2, 24);
    dst = (a0 * b0) + (a1 * b1) + (a2 * b2) + (a3 * b3);
    return dst;
}
unsigned _dotpu4(unsigned src1, unsigned src2)
{
    unsigned int dst;
    unsigned int a0, a1, a2, a3;
    unsigned int b0, b1, b2, b3;
    a0 = _extur(src1, (24 << 5) + 24);
    a1 = _extur(src1, (16 << 5) + 24);
    a2 = _extur(src1, (8 << 5) + 24);
    a3 = _extur(src1, 24);
    b0 = _extur(src2, (24 << 5) + 24);
    b1 = _extur(src2, (16 << 5) + 24);
    b2 = _extur(src2, (8 << 5) + 24);
    b3 = _extur(src2, 24);
    dst = (a0 * b0) + (a1 * b1) + (a2 * b2) + (a3 * b3);
    return dst;
}
long long _dpack2(unsigned src1, unsigned src2)
{
    long long dst;
    unsigned int dst_o, dst_e;
    dst_o = (_extu(src1,  0, 16) << 16) & 0xFFFF0000;
    dst_e = (_extu(src1, 16, 16) << 16) & 0xFFFF0000;
    dst_o |= _extu(src2,  0, 16) & 0x0000FFFF;
    dst_e |= _extu(src2, 16, 16) & 0x0000FFFF;
    dst = ((long long)dst_o << 32) & 0xFFFFFFFF00000000;
    dst |= (long long)dst_e & 0x00000000FFFFFFFF;
    return dst;
}
long long _dpackx2(unsigned src1, unsigned src2)
{
    long long dst;
    unsigned int dst_o, dst_e;
    dst_o = (_extu(src2, 16, 16) << 16) & 0xFFFF0000;
    dst_e = (_extu(src1, 16, 16) << 16) & 0xFFFF0000;
    dst_o |= _extu(src1,  0, 16) & 0x0000FFFF;
    dst_e |= _extu(src2,  0, 16) & 0x0000FFFF;
    dst = ((long long)dst_o << 32) & 0xFFFFFFFF00000000;
    dst |= (long long)dst_e & 0x00000000FFFFFFFF;
    return dst;
}
__int40_t _dtol(double src)
{
    return (__int40_t)_dtoll(src);
}
long long _dtoll(double src)
{
    long long dst;
    memcpy(&dst, &src, sizeof(long long));
    return dst;
}
