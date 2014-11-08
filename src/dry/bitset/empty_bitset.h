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
  std::size_t size() const noexcept {
    return 0;
  }

  /**
   * @copydoc bitset::count()
   */
  std::size_t count(bool value = true) const noexcept {
    static_cast<void>(value);
    return 0;
  }

  /**
   * @copydoc bitset::all()
   */
  bool all() const noexcept {
    return false;
  }

  /**
   * @copydoc bitset::any()
   */
  bool any() const noexcept {
    return false;
  }

  /**
   * @copydoc bitset::none()
   */
  bool none() const noexcept {
    return true;
  }

  /**
   * @copydoc bitset::test()
   */
  bool test(std::size_t pos) const {
    static_cast<void>(pos);
    throw std::out_of_range{"pos >= size()"};
  }

  /**
   * @copydoc bitset::operator[]()
   */
  bool operator[](std::size_t pos) const noexcept {
    static_cast<void>(pos);
    return false;
  }

  /**
   * @copydoc bitset::clear()
   */
  empty_bitset& clear() noexcept {
    /* nothing to do */
    return *this;
  }

  /**
   * @copydoc bitset::set()
   */
  empty_bitset& set() noexcept {
    /* nothing to do */
    return *this;
  }

  /**
   * @copydoc bitset::set(std::size_t,bool)
   */
  empty_bitset& set(std::size_t pos, bool value = true) {
    static_cast<void>(pos);
    static_cast<void>(value);
    throw std::out_of_range{"pos >= size()"};
  }

  /**
   * @copydoc bitset::reset()
   */
  empty_bitset& reset() noexcept {
    /* nothing to do */
    return *this;
  }

  /**
   * @copydoc bitset::reset(std::size_t)
   */
  empty_bitset& reset(std::size_t pos) {
    return set(pos, false);
  }

  /**
   * @copydoc bitset::flip()
   */
  empty_bitset& flip() noexcept {
    /* nothing to do */
    return *this;
  }
};

#endif /* DRY_EMPTY_BITSET_H */
