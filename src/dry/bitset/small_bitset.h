/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_SMALL_BITSET_H
#define DRY_SMALL_BITSET_H

/**
 * @file
 */

#include "../bitset.h"

#include <algorithm> /* for std::count_if(), std::fill_n(), std::min() */
#include <array>     /* for std::array */
#include <limits>    /* for std::numeric_limits */

namespace dry {
  template <std::size_t N>
  class small_bitset;
}

/**
 * A small bitset, capable of storing a maximum of N-1 set bits.
 *
 * The default capacity (N = 16) is designed to correspond to the size of a
 * single L1 cache line on the x86/x86-64 architecture.
 */
template <std::size_t N = 16>
class dry::small_bitset : public dry::bitset<small_bitset<N>> {
  using entry_type = std::uint32_t;
  std::array<entry_type, N> _data {{0}};

public:
  /**
   * Default constructor.
   */
  small_bitset() noexcept = default;

  /**
   * Constructor.
   */
  small_bitset(std::size_t size) {
    if (size > std::numeric_limits<entry_type>::max()) {
      throw std::out_of_range{"size too large"};
    }
    _data[0] = size;
    std::fill_n(_data.begin() + 1, N - 1, 0);
  }

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
   * Returns a reference to the internal data array.
   */
  inline std::array<entry_type, N>& data() noexcept {
    return _data;
  }

  /**
   * Returns a const reference to the internal data array.
   */
  inline const std::array<entry_type, N>& data() const noexcept {
    return _data;
  }

  /**
   * @copydoc bitset::size()
   */
  inline std::size_t size() const noexcept {
    return _data[0];
  }

  /**
   * @copydoc bitset::count()
   */
  inline std::size_t count(bool value = true) const noexcept {
    if (!size()) return 0;
    const auto count = std::count_if(_data.begin() + 1, _data.end(),
      [](const entry_type entry){ return entry != 0; });
    return value ? count : size() - count;
  }

  /**
   * @copydoc bitset::all()
   */
  inline bool all() const noexcept {
    return size() && std::all_of(_data.begin() + 1, _data.end(),
      [](const entry_type entry){ return entry != 0; });
  }

  /**
   * @copydoc bitset::any()
   */
  inline bool any() const noexcept {
    return size() && std::any_of(_data.begin() + 1, _data.end(),
      [](const entry_type entry){ return entry != 0; });
  }

  /**
   * @copydoc bitset::none()
   */
  inline bool none() const noexcept {
    return !size() || std::none_of(_data.begin() + 1, _data.end(),
      [](const entry_type entry){ return entry != 0; });
  }

  /**
   * @copydoc bitset::flip()
   */
  small_bitset& flip() noexcept; /* not supported */
};

#endif /* DRY_SMALL_BITSET_H */
