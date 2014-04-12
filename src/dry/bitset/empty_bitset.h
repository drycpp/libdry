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
  inline std::size_t size() const noexcept {
    return 0;
  }

  /**
   * @copydoc bitset::count()
   */
  inline std::size_t count(bool value = true) const noexcept {
    return (void)value, 0;
  }

  /**
   * @copydoc bitset::all()
   */
  inline bool all() const noexcept {
    return false;
  }

  /**
   * @copydoc bitset::any()
   */
  inline bool any() const noexcept {
    return false;
  }

  /**
   * @copydoc bitset::none()
   */
  inline bool none() const noexcept {
    return true;
  }

  /**
   * @copydoc bitset::test()
   */
  inline bool test(std::size_t pos) const {
    if (pos >= size()) {
      throw std::out_of_range{"pos >= size()"};
    }
    return false;
  }

  /**
   * @copydoc bitset::operator[]()
   */
  inline bool operator[](std::size_t pos) const noexcept {
    return (void)pos, false;
  }

  /**
   * @copydoc bitset::flip()
   */
  empty_bitset& flip() noexcept {
    return *this;
  }
};

#endif /* DRY_EMPTY_BITSET_H */
