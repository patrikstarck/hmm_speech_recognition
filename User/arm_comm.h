/***************************************************************************
 **
 **    Common definition for IAR EW ARM
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 39 $
 **
 ***************************************************************************/
#include <intrinsics.h>

#ifndef __ARM_COMM_DEF_H
#define __ARM_COMM_DEF_H

typedef double                Flo64;    // Double precision floating point
typedef double              * pFlo64;
typedef float                 Flo32;    // Single precision floating point
typedef float               * pFlo32;
typedef signed   long long    Int64S;   // Signed   64 bit quantity
typedef signed   long long  * pInt64S;
typedef unsigned long long    Int64U;   // Unsigned 64 bit quantity
typedef unsigned long long  * pInt64U;
typedef signed   int          Int32S;   // Signed   32 bit quantity
typedef signed   int        * pInt32S;
typedef unsigned int          Int32U;   // Unsigned 32 bit quantity
typedef unsigned int        * pInt32U;
typedef signed   short        Int16S;   // Signed   16 bit quantity
typedef signed   short      * pInt16S;
typedef unsigned short        Int16U;   // Unsigned 16 bit quantity
typedef unsigned short      * pInt16U;
typedef signed   char         Int8S;    // Signed    8 bit quantity
typedef signed   char       * pInt8S;
typedef unsigned char         Int8U;    // Unsigned  8 bit quantity
typedef unsigned char       * pInt8U;
typedef unsigned int          Boolean;  // Boolean
typedef unsigned int        * pBoolean;


extern Int32U CriticalSecCntr;

typedef void * (*CommUserFpnt_t)(void *);
typedef void   (*VoidFpnt_t)(void);
typedef signed short  * ps16;
typedef unsigned long  * pu32;
typedef unsigned short * pu16;
typedef unsigned char  * pu8;

typedef float               * pf32;
typedef float                 f32;

#ifndef FALSE
#define FALSE (1 == 0)
#endif

#ifndef TRUE
#define TRUE  (1 == 1)
#endif

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define _2BL(a)   (u8)(a),(u8)(a>>8)
#define _2BB(a)   (u8)(a>>8),(u8)(a),
#define _3BL(a)   (u8)(a),(u8)(a>>8),(u8)(a>>16)
#define _3BB(a)   (u8)(a>>16),(u8)(a>>8),(u8)(a)
#define _4BL(a)   (u8)(a),(u8)(a>>8),(u8)(a>>16),(u8)(a>>24)
#define _4BB(a)   (u8)(a>>24),(u8)(a>>16),(u8)(a>>8),(u8)(a)

#define MHZ           *1000000l
#define KHZ           *1000l
#define HZ            *1l

#ifndef NULL
#define NULL ((void*)0)
#endif
// Atomic exchange of data between a memory cell and a register
// return value of the memory cell
#if __CORE__ < 7

#define IRQ_FLAG        0x80
#define FIQ_FLAG        0x40
inline __arm u32 AtomicExchange (u32 State, pu32 Flag)
{
  asm("swp  r0, r0, [r1]");
  return(State);
}


inline __arm u32 EntrCritSection(void)
{
unsigned long tmp;
  tmp = __get_CPSR();
  __set_CPSR(tmp | IRQ_FLAG);
  return(tmp);
}

inline __arm void ExtCritSection(u32 Save)
{
unsigned long tmp;
  tmp = __get_CPSR();
  __set_CPSR(tmp & (Save | ~IRQ_FLAG));
}

inline __arm u32 EntrCritSectionFiq(void)
{
unsigned long tmp;
  tmp = __get_CPSR();
  __set_CPSR(tmp | (IRQ_FLAG | FIQ_FLAG));
  return(tmp);
}

inline __arm void ExtCritSectionFiq(u32 Save)
{
unsigned long tmp;
  tmp = __get_CPSR();
  __set_CPSR(tmp & (Save | ~(IRQ_FLAG | FIQ_FLAG)));
}

#define ENTR_CRT_SECTION(Save) Save = EntrCritSection()
#define EXT_CRT_SECTION(Save)  ExtCritSection(Save)

#define ENTR_CRT_SECTION_F(Save) Save = EntrCritSectionFiq()
#define EXT_CRT_SECTION_F(Save)  ExtCritSectionFiq(Save)

#elif  __CORE__ == 7



inline void EntrCritSection(void)
{
  if(CriticalSecCntr == 0)
  {
    asm("CPSID i");
  }
  // avoid lost of one count in case of simultaneously calling from both places
  ++CriticalSecCntr;
}

inline void ExtCritSection(void)
{
  if(--CriticalSecCntr == 0)
  {
    asm("CPSIE i");
  }
}

inline Int32U AtomicExchange (Int32U State, pInt32U Flag)
{
Int32U Hold;
  EntrCritSection();
  Hold = *Flag;
  *Flag = State;
  ExtCritSection();
  return(Hold);
}

#define ENTR_CRT_SECTION() EntrCritSection()
#define EXT_CRT_SECTION()  ExtCritSection()
#endif

#define LongToBin(n) (((n >> 21) & 0x80) | \
                      ((n >> 18) & 0x40) | \
                      ((n >> 15) & 0x20) | \
                      ((n >> 12) & 0x10) | \
                      ((n >>  9) & 0x08) | \
                      ((n >>  6) & 0x04) | \
                      ((n >>  3) & 0x02) | \
                      ((n      ) & 0x01))

#define __BIN(n) LongToBin(0x##n##l)

#define BIN8(n)                       __BIN(n)
#define BIN(n)                        __BIN(n)
#define BIN16(b1,b2)        ((        __BIN(b1)  <<  8UL) + \
                                      __BIN(b2))
#define BIN32(b1,b2,b3,b4) ((((u32)__BIN(b1)) << 24UL) + \
                            (((u32)__BIN(b2)) << 16UL) + \
                            (((u32)__BIN(b3)) <<  8UL) + \
                              (u32)__BIN(b4))

#endif // __ARM_COMM_DEF_H
