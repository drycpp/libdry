/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_BITSET_H
#define DRY_BITSET_H

/**
 * @file
 */

#include <cassert>     /* for assert() */
#include <cstddef>     /* for std::size_t */
#include <cstdint>     /* for std::uint64_t */
#include <type_traits> /* for std::is_same<> */

namespace dry {
  template <class Derived, typename Word>
  class bitset;
}

/**
 * A bitset.
 *
 * @abstract
 * @see http://en.wikipedia.org/wiki/Bit_array
 */
template <class Derived, typename Word>
class dry::bitset {
protected:
  /**
   * Default constructor.
   */
  bitset() noexcept = default;

public:
  using size_type = std::size_t;
  using word_type = Word;

  static constexpr size_type npos = static_cast<size_type>(-1);

  static constexpr size_type word_size = sizeof(word_type) * 8;

  /**
   * Copy constructor.
   */
  bitset(const bitset& other) noexcept = default;

  /**
   * Move constructor.
   */
  bitset(bitset&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~bitset() noexcept = default;

  /**
   * Copy assignment operator.
   */
  bitset& operator=(const bitset& other) noexcept = default;

  /**
   * Move assignment operator.
   */
  bitset& operator=(bitset&& other) noexcept = default;

  /**
   * Checks whether this bitset is empty.
   */
  inline bool empty() const noexcept {
    return size() == 0;
  }

  /**
   * Returns the number of bits in this bitset.
   */
  inline size_type size() const noexcept {
    static_assert(!std::is_same<decltype(&Derived::size),
      decltype(&bitset<Derived, Word>::size)>::value,
      "unimplemented static polymorphic method 'size' in derived class");
    return static_cast<const Derived&>(*this).size();
  }
};

namespace dry {
  template <class Derived, typename Word>
  constexpr std::size_t bitset<Derived, Word>::npos;

  template <class Derived, typename Word>
  constexpr std::size_t bitset<Derived, Word>::word_size;
}

#endif /* DRY_BITSET_H */
