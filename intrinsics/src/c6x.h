#ifndef C6X_H
#define C6X_H
#include "std.h"

/**
 * @brief ABS
 *
 * Returns the saturated absolute value of src
 *
 * @param src
 * @return int
 */
int _abs(int src);
__int40_t _labs(__int40_t src);

/**
 * @brief ABS2
 *
 * Calculates the absolute value for each 16-bit value
 *
 * @param src
 * @return int
 */
int _abs2(int src);

/**
 * @brief ADD2
 *
 * Adds the upper and lower halves of src1 to the upper and lower
 * halves of src2 and returns the result. Any overflow from the lower
 * half add does not affect the upper half add.
 *
 * @param src1
 * @param src2
 * @return int
 */
int _add2(int src1, int src2);

/**
 * @brief ADD4
 *
 * Performs 2s-complement addition to pairs of packed 8-bit numbers
 *
 * @param src1
 * @param src2
 * @return int
 */
int _add4(int src1, int src2);

/**
 * @brief ADDSUB
 *
 * Performs an addition and subtraction in parallel.
 *
 * @param src1
 * @param src2
 * @return long
 */
long long _addsub(int src1, int src2);

/**
 * @brief ADDSUB2
 *
 * Performs an ADD2 and SUB2 in parallel.
 *
 * @param src1
 * @param src2
 * @return long
 */
long long _addsub2(int src1, int src2);

/**
 * @brief AVG2
 *
 * Calculates the average for each pair of signed 16-bit values
 *
 * @param src1
 * @param src2
 * @return int
 */
int _avg2(int src1, int src2);

/**
 * @brief AVGU4
 *
 * Calculates the average for each pair of signed 8-bit values
 *
 * @param src1
 * @param src2
 * @return unsigned
 */
unsigned int _avgu4(unsigned int src1, unsigned int src2);

/**
 * @brief BITC4
 *
 * For each of the 8-bit quantities in src, the number of 1 bits is written
 * to the corresponding position in the return value
 *
 * @param src
 * @return unsigned
 */
unsigned int _bitc4(unsigned int src);

/**
 * @brief BITR
 *
 * Reverses the order of the bits
 *
 * @param src
 * @return unsigned
 */
unsigned int _bitr(unsigned int src);

/**
 * @brief CLR
 *
 * Clears the specified field in src2. The beginning and ending bits of
 * the field to be cleared are specified by csta and cstb, respectively.
 *
 * @param src2
 * @param csta
 * @param cstb
 * @return unsigned
 */
unsigned int _clr(unsigned int src2, unsigned int csta, unsigned int cstb);
/**
 * @brief CLR
 *
 * Clears the specified field in src2. The beginning and ending bits of
 * the field to be cleared are specified by the lower 10 bits of src1.
 *
 * @param src2
 * @param src1
 * @return unsigned
 */
unsigned int _clrr(unsigned int src2, int src1);

/**
 * @brief 
 * 
 * @param src2 
 * @param csta 
 * @param cstb 
 * @return int 
 */
int _ext(int src2, unsigned csta, unsigned cstb);

/**
 * @brief EXT
 *
 * Extracts the specified field in src2, sign-extended to 32 bits. The
 * extract is performed by a shift left followed by a signed shift right;
 * the shift left and shift right amounts are specified by the lower 10
 * bits of src1.
 *
 * @param src2
 * @param src1
 * @return int
 */
int _extr(int src2, int src1);
/**
 * @brief EXTU
 *
 * Extracts the specified field in src2, zero-extended to 32 bits. The
 * extract is performed by a shift left followed by a unsigned shift right;
 * csta and cstb are the shift left and shift right amounts, respectively.
 *
 * @param src2
 * @param csta
 * @param cstb
 * @return unsigned
 */
unsigned int _extu(unsigned int src2, unsigned int csta, unsigned int cstb);
/**
 * @brief EXTU
 *
 * Extracts the specified field in src2, zero-extended to 32 bits. The
 * extract is performed by a shift left followed by a unsigned shift right;
 * the shift left and shift right amounts are specified by the lower 10
 * bits of src1.
 *
 * @param src2
 * @param src1
 * @return unsigned
 */
unsigned int _extur(unsigned int src2, int src1);

/**
 * @brief CMPEQ2
 * 
 * Performs equality comparisons on each pair of 16-bit values.
 * Equality results are packed into the two least-significant bits of the
 * return value.
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _cmpeq2(int src1, int src2);
/**
 * @brief CMPEQ4
 * 
 * Performs equality comparisons on each pair of 8-bit values. Equality
 * results are packed into the four least-significant bits of the return
 * value.
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _cmpeq4(int src1, int src2);
/**
 * @brief CMPGT2
 * 
 * Compares each pair of signed 16-bit values. Results are packed
 * into the two least-significant bits of the return value.
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _cmpgt2(int src1, int src2);
/**
 * @brief CMPGTU4
 * 
 * Compares each pair of 8-bit values. Results are packed into the four
 * least-significant bits of the return value.
 * 
 * @param src1 
 * @param src2 
 * @return unsigned 
 */
unsigned _cmpgtu4(unsigned src1, unsigned src2);
/**
 * @brief CMPLT2
 * 
 * Swaps operands and calls _cmpgt2. This is defined as a macro.
 * You must include c6x.h.
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _cmplt2(int src1, int src2);
/**
 * @brief CMPLTU4
 * 
 * Swaps operands and calls _cmpgtu4. This is defined as a macro.
 * You must include c6x.h.
 * 
 * @param src1 
 * @param src2 
 * @return unsigned 
 */
unsigned _cmpltu4(unsigned src1, unsigned src2);
/**
 * @brief CMPY
 * 
 * Performs various complex multiply operations.
 * 
 * @param src1 
 * @param src2 
 * @return long 
 */
long long _cmpy(unsigned src1, unsigned src2);
/**
 * @brief CMPYR
 * 
 * @param src1 
 * @param src2 
 * @return unsigned 
 */
unsigned _cmpyr(unsigned src1, unsigned src2);
/**
 * @brief CMPYR1
 * 
 * @param src1 
 * @param src2 
 * @return unsigned 
 */
unsigned _cmpyr1(unsigned src1, unsigned src2);
/**
 * @brief DDOTP4
 * 
 * @param src1 
 * @param src2 
 * @return long 
 */
long long _ddotp4(unsigned src1, unsigned src2);
/**
 * @brief DDOTPH2
 * 
 * @param src1 
 * @param src2 
 * @return long 
 */
long long _ddotph2(long long src1, unsigned src2);
/**
 * @brief DDOTPL2
 * 
 * @param src1 
 * @param src2 
 * @return long 
 */
long long _ddotpl2(long long src1, unsigned src2);
/**
 * @brief DDOTPH2R
 * 
 * @param src1 
 * @param src2 
 * @return unsigned 
 */
unsigned _ddotph2r(long long src1, unsigned src2);
/**
 * @brief DDOTPL2R
 * 
 * @param src1 
 * @param src2 
 * @return unsigned 
 */
unsigned _ddotpl2r(long long src1, unsigned src2);
/**
 * @brief DEAL
 * 
 * @param src 
 * @return unsigned 
 */
unsigned _deal(unsigned src);
/**
 * @brief DMV
 * 
 * @param src1 
 * @param src2 
 * @return long 
 */
long long _dmv(int src1, int src2);
/**
 * @brief DDOTP2
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _dotp2(int src1, int src2);
/**
 * @brief LDOTP2
 * 
 * @param src1 
 * @param src2 
 * @return __int40_t 
 */
__int40_t _ldotp2(int src1, int src2);
/**
 * @brief DOTPN2
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _dotpn2(int src1, int src2);
/**
 * @brief DOTPNRSU2
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _dotpnrsu2(int src1, unsigned src2);
/**
 * @brief DOTPNRUS2
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _dotpnrus2(unsigned src1, int src2);
/**
 * @brief DOTPRSU2
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _dotprsu2(int src1, unsigned src2);
/**
 * @brief DOTPSU4
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _dotpsu4(int src1, unsigned src2);
/**
 * @brief DOTPUS4
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _dotpus4(unsigned src1, int src2);
/**
 * @brief DOTPU4
 * 
 * @param src1 
 * @param src2 
 * @return unsigned 
 */
unsigned _dotpu4(unsigned src1, unsigned src2);
/**
 * @brief DPACK2
 * 
 * @param src1 
 * @param src2 
 * @return long 
 */
long long _dpack2(unsigned src1, unsigned src2);
/**
 * @brief DPACKX2
 * 
 * @param src1 
 * @param src2 
 * @return long 
 */
long long _dpackx2(unsigned src1, unsigned src2);
/**
 * @brief 
 * 
 * @param src 
 * @return __int40_t 
 */
__int40_t _dtol(double src);
/**
 * @brief DTOLL
 * 
 * @param src 
 * @return long 
 */
long long _dtoll(double src);

/**
 * @brief SADD
 * 
 * Adds src1 to src2 and saturates the result. Returns the result.
 * 
 * @param src1 
 * @param src2 
 * @return int 
 */
int _sadd (int src1, int src2);

#endif // C6X_H
