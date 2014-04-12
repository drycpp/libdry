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
   * @copydoc bitset::size()
   */
  inline size_type size() const noexcept {
    return _size;
  }
};

#endif /* DRY_UNIFORM_BITSET_H */
