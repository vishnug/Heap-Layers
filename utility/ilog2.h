// -*- C++ -*-

#ifndef HL_ILOG2_H
#define HL_ILOG2_H

#if defined(_WIN32)
#include <intrn.h>
#endif

namespace HL {

  /// Quickly calculate the CEILING of the log (base 2) of the argument.
#if defined(_WIN32)
  static inline int ilog2 (size_t sz)
  {
    int retval;
    sz = (sz << 1) - 1;
    _BitScanForward (&retval, sz);
    return retval;
  }
#elif defined(__GNUC__) && defined(__i386__)
  static inline int ilog2 (size_t sz)
  {
    sz = (sz << 1) - 1;
    asm ("bsrl %0, %0" : "=r" (sz) : "0" (sz));
    return (int) sz;
  }
#elif 0 // defined(__GNUC__) && defined(__x86_64__)
  static inline int ilog2 (size_t sz)
  {
    sz = (sz << 1) - 1;
    asm ("bsrq %0, %0" : "=r" (sz) : "0" (sz));
    return (int) sz;
  }
#elif defined(__GNUC__)
  // Just use the intrinsic.
  static inline int ilog2 (size_t sz)
  {
    sz = (sz << 1) - 1;
    return (int) ((sizeof(unsigned long) * 8) - __builtin_clzl(sz) - 1);
  }
#else
  static inline int ilog2 (size_t v) {
    int log = 0;
    unsigned int value = 1;
    while (value < v) {
      value <<= 1;
      log++;
    }
    return log;
  }
#endif


}

#endif
