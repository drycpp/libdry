/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_SMALL_BITSET_H
#define DRY_SMALL_BITSET_H

/**
 * @file
 */

#include "../bitset.h"

#include <array> /* for std::array */

namespace dry {
  template <std::size_t N>
  class small_bitset;
}

/**
 * A small bitset, capable of storing a maximum of N entries.
 *
 * The default capacity (N = 16) is designed to correspond to the size of a
 * single L1 cache line on the x86/x86-64 architecture.
 */
template <std::size_t N = 16>
class dry::small_bitset : public dry::bitset<small_bitset<N>> {
  std::array<std::uint32_t, N> _data;

public:
  /**
   * Default constructor.
   */
  small_bitset() noexcept = default;

  /**
   * Copy constructor.
   */
  small_bitset(const small_bitset& other) noexcept = default;

  /**
   * Move constructor.
   */
  small_bitset(small_bitset&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~small_bitset() noexcept = default;

  /**
   * Copy assignment operator.
   */
  small_bitset& operator=(const small_bitset& other) noexcept = default;

  /**
   * Move assignment operator.
   */
  small_bitset& operator=(small_bitset&& other) noexcept = default;

  /**
   * @copydoc bitset::size()
   */
  inline std::size_t size() const noexcept {
    return 0; // TODO
  }

  /**
   * @copydoc bitset::flip()
   */
  small_bitset& flip() noexcept {
    // TODO
    return *this;
  }
};

#endif /* DRY_SMALL_BITSET_H */
