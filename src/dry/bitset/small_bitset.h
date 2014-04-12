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
  static constexpr entry_type npos = static_cast<entry_type>(-1);

  /**
   * Default constructor.
   */
  small_bitset() noexcept = default;

  /**
   * Constructor.
   */
  small_bitset(std::size_t size) {
    if (size > std::numeric_limits<entry_type>::max() - 1) {
      throw std::out_of_range{"size too large"};
    }
    _data[0] = size;
    std::fill_n(_data.begin() + 1, N - 1, npos);
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
  std::array<entry_type, N>& data() noexcept {
    return _data;
  }

  /**
   * Returns a const reference to the internal data array.
   */
  const std::array<entry_type, N>& data() const noexcept {
    return _data;
  }

  /**
   * @copydoc bitset::size()
   */
  std::size_t size() const noexcept {
    return _data[0];
  }

  /**
   * @copydoc bitset::count()
   */
  std::size_t count(bool value = true) const noexcept {
    if (!size()) return 0;
    const auto begin = _data.begin() + 1;
    const auto end = begin + std::min(size(), N - 1);
    const auto count = std::count_if(begin, end,
      [](const entry_type entry){ return entry != npos; });
    return value ? count : size() - count;
  }

  /**
   * @copydoc bitset::all()
   */
  bool all() const noexcept {
    return size() && size() < N && size() == count();
  }

  /**
   * @copydoc bitset::any()
   */
  bool any() const noexcept {
    const auto begin = _data.begin() + 1;
    const auto end = begin + std::min(size(), N - 1);
    return size() && std::any_of(begin, end,
      [](const entry_type entry){ return entry != npos; });
  }

  /**
   * @copydoc bitset::none()
   */
  bool none() const noexcept {
    const auto begin = _data.begin() + 1;
    const auto end = begin + std::min(size(), N - 1);
    return !size() || std::none_of(begin, end,
      [](const entry_type entry){ return entry != npos; });
  }

  /**
   * @copydoc bitset::test()
   */
  bool test(std::size_t pos) const {
    if (pos >= size()) {
      throw std::out_of_range{"pos >= size()"};
    }
    return operator[](pos);
  }

  /**
   * @copydoc bitset::operator[]()
   */
  bool operator[](std::size_t pos) const noexcept {
    const auto begin = _data.begin() + 1;
    const auto end = begin + std::min(size(), N - 1);
    return size() && std::find(begin, end, pos) != end;
  }

  /**
   * @copydoc bitset::set()
   */
  small_bitset& set() {
    if (size() >= N) {
      throw std::domain_error{"cannot set() all bits when size() >= N"};
    }
    for (auto pos = 1U; pos <= std::min(size(), N - 1); pos++) {
      _data[pos] = pos - 1;
    }
    return *this;
  }

  /**
   * @copydoc bitset::set(std::size_t,bool)
   */
  small_bitset& set(std::size_t pos, bool value = true) {
    if (pos >= size()) {
      throw std::out_of_range{"pos >= size()"};
    }
    const auto begin = _data.begin() + 1;
    const auto end = begin + std::min(size(), N - 1);
    auto it = std::find(begin, end, pos);
    if (it != end) {
      if (!value) {
        std::fill(std::remove(it, end, pos), end, npos);
      }
    }
    else if (value) {
      it = std::find(begin, end, npos);
      if (it == end) {
        throw std::overflow_error{"cannot set() more bits"};
      }
      *it = pos;
    }
    return *this;
  }

  /**
   * @copydoc bitset::reset()
   */
  small_bitset& reset() noexcept {
    if (size()) {
      std::fill_n(_data.begin() + 1, N - 1, npos);
    }
    return *this;
  }

  /**
   * @copydoc bitset::reset(std::size_t)
   */
  small_bitset& reset(std::size_t pos) {
    return set(pos, false);
  }

  /**
   * @copydoc bitset::flip()
   */
  small_bitset& flip() noexcept; /* not supported */
};

namespace dry {
  template <std::size_t N>
  constexpr typename small_bitset<N>::entry_type small_bitset<N>::npos;
}

#endif /* DRY_SMALL_BITSET_H */
