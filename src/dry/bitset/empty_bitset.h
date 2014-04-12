/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_EMPTY_BITSET_H
#define DRY_EMPTY_BITSET_H

/**
 * @file
 */

#include "../bitset.h"

namespace dry {
  class empty_bitset;
}

/**
 * An empty bitset.
 */
class dry::empty_bitset : public dry::bitset<empty_bitset> {
public:
  /**
   * Default constructor.
   */
  empty_bitset() noexcept = default;

  /**
   * Copy constructor.
   */
  empty_bitset(const empty_bitset& other) noexcept = default;

  /**
   * Move constructor.
   */
  empty_bitset(empty_bitset&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~empty_bitset() noexcept = default;

  /**
   * Copy assignment operator.
   */
  empty_bitset& operator=(const empty_bitset& other) noexcept = default;

  /**
   * Move assignment operator.
   */
  empty_bitset& operator=(empty_bitset&& other) noexcept = default;

  /**
   * @copydoc bitset::size()
   */
  inline size_type size() const noexcept {
    return 0;
  }
};

#endif /* DRY_EMPTY_BITSET_H */
