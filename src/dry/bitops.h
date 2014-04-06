/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_BITOPS_H
#define DRY_BITOPS_H

/**
 * @file
 */

#include <cstdint> /* for std::uint64_t */

namespace dry {
  /**
   * Returns the number of 1-bits in `word`.
   */
  static inline unsigned int
  popcount64(const std::uint64_t word) {
    static_assert(sizeof(word) <= sizeof(unsigned long long),
      "__builtin_popcountll() word size mismatch");
    return __builtin_popcountll(word);
  }
}

#endif /* DRY_BITOPS_H */
