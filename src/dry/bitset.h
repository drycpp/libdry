/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_BITSET_H
#define DRY_BITSET_H

/**
 * @file
 */

#include <cassert>     /* for assert() */
#include <cstddef>     /* for std::size_t */
#include <cstdint>     /* for std::uint64_t */
#include <stdexcept>   /* for std::out_of_range */
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
template <class Derived, typename Word = std::uint64_t>
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

  /**
   * Returns the number of set bits in this bitset.
   */
  inline size_type count(bool value = true) const noexcept;

  /**
   * Checks whether all bits are set in this bitset.
   */
  inline bool all() const noexcept;

  /**
   * Checks whether any bits are set in this bitset.
   */
  inline bool any() const noexcept;

  /**
   * Checks whether all bits are unset in this bitset.
   */
  inline bool none() const noexcept;

  /**
   * Checks whether a given bit is set in this bitset.
   */
  inline bool test(size_type pos) const;

  /**
   * Checks whether a given bit is set in this bitset.
   */
  inline bool operator[](size_type pos) const;

  /**
   * Sets all bits in this bitset.
   */
  bitset& set();

  /**
   * Clears all bits in this bitset.
   */
  bitset& reset();

  /**
   * Inverts all bits in this bitset.
   */
  bitset& flip() noexcept;
};

namespace dry {
  template <class Derived, typename Word>
  constexpr std::size_t bitset<Derived, Word>::npos;

  template <class Derived, typename Word>
  constexpr std::size_t bitset<Derived, Word>::word_size;
}

#endif /* DRY_BITSET_H */
