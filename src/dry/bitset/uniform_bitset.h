/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_UNIFORM_BITSET_H
#define DRY_UNIFORM_BITSET_H

/**
 * @file
 */

#include "../bitset.h"

namespace dry {
  class uniform_bitset;
}

/**
 * A uniform bitset, always returning the same value.
 */
class dry::uniform_bitset : public dry::bitset<uniform_bitset> {
  std::size_t _size {0};
  bool _value {false};

public:
  /**
   * Default constructor.
   */
  uniform_bitset() noexcept = default;

  /**
   * Constructor.
   */
  uniform_bitset(std::size_t size, bool value = false) noexcept
    : _size{size}, _value{value} {}

  /**
   * Copy constructor.
   */
  uniform_bitset(const uniform_bitset& other) noexcept = default;

  /**
   * Move constructor.
   */
  uniform_bitset(uniform_bitset&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~uniform_bitset() noexcept = default;

  /**
   * Copy assignment operator.
   */
  uniform_bitset& operator=(const uniform_bitset& other) noexcept = default;

  /**
   * Move assignment operator.
   */
  uniform_bitset& operator=(uniform_bitset&& other) noexcept = default;

  /**
   * Returns the current value of this bitset.
   */
  inline bool value() const noexcept {
    return _value;
  }

  /**
   * @copydoc bitset::size()
   */
  inline std::size_t size() const noexcept {
    return _size;
  }

  /**
   * @copydoc bitset::count()
   */
  inline std::size_t count(bool value = true) const noexcept {
    return (value == _value) ? size() : 0;
  }

  /**
   * @copydoc bitset::all()
   */
  inline bool all() const noexcept {
    return _value;
  }

  /**
   * @copydoc bitset::any()
   */
  inline bool any() const noexcept {
    return _value;
  }

  /**
   * @copydoc bitset::none()
   */
  inline bool none() const noexcept {
    return !_value;
  }

  /**
   * @copydoc bitset::test()
   */
  inline bool test(std::size_t pos) const {
    if (pos >= size()) {
      throw std::out_of_range{"pos >= size()"};
    }
    return _value;
  }

  /**
   * @copydoc bitset::flip()
   */
  uniform_bitset& flip() noexcept {
    _value = !_value;
    return *this;
  }
};

#endif /* DRY_UNIFORM_BITSET_H */
