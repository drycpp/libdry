/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_DENSE_BITSET_H
#define DRY_DENSE_BITSET_H

/**
 * @file
 */

#include "../bitset.h"

#include <algorithm>  /* for std::*() */
#include <functional> /* for std::function */
#include <vector>     /* for std::vector */

namespace dry {
  class dense_bitset;
}

/**
 * A dense bitset.
 *
 * Dense bitsets require storage proportional to the total range of bits
 * they represent.
 */
class dry::dense_bitset : public dry::bitset<dense_bitset, std::uint64_t> {
  std::size_t _size {0};           /* size in bits */
  std::vector<word_type> _words;   /* array of words */

public:
  /**
   * Default constructor.
   */
  dense_bitset() = default;

  /**
   * Constructor.
   *
   * @throws std::bad_alloc if out of memory.
   */
  dense_bitset(const std::size_t size,
               const bool default_value = false) {
    resize(size, default_value);
  }

  /**
   * Copy constructor.
   */
  dense_bitset(const dense_bitset& other) = default;

  /**
   * Move constructor.
   */
  dense_bitset(dense_bitset&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~dense_bitset() noexcept = default;

  /**
   * Copy assignment operator.
   */
  dense_bitset& operator=(const dense_bitset& other) = default;

  /**
   * Move assignment operator.
   */
  dense_bitset& operator=(dense_bitset&& other) noexcept = default;

  std::vector<word_type>& words() noexcept {
    return _words;
  }

  const std::vector<word_type>& words() const noexcept {
    return _words;
  }

  /**
   * @copydoc bitset::size()
   */
  std::size_t size() const noexcept {
    return _size;
  }

  /**
   * @copydoc bitset::count()
   */
  std::size_t count(bool value = true) const noexcept {
    return (void)value, 0; // TODO
  }

  /**
   * @copydoc bitset::all()
   */
  bool all() const noexcept {
    if (empty()) return false;
    // FIXME: implement a special case for the last word.
    return std::all_of(_words.begin(), _words.end(), [](const word_type word) {
      return word == static_cast<word_type>(-1);
    });
  }

  /**
   * @copydoc bitset::any()
   */
  bool any() const noexcept {
    return std::any_of(_words.begin(), _words.end(), [](const word_type word) {
      return word != 0;
    });
  }

  /**
   * @copydoc bitset::none()
   */
  bool none() const noexcept {
    return std::none_of(_words.begin(), _words.end(), [](const word_type word) {
      return word != 0;
    });
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
    assert(pos < size());
    const auto& word = _words[pos / word_size];
    return word & (1UL << (pos & (word_size - 1UL)));
  }

  /**
   * @throws std::bad_alloc if out of memory
   */
  dense_bitset& resize(const std::size_t new_size,
                       const bool default_value = false) {
    const auto old_size = _size;
    _size = new_size;
    _words.resize((new_size + word_size - 1) / word_size);
    if (default_value && new_size > old_size) {
      // TODO: set_n(old_size, new_size - old_size, default_value);
    }
    return *this;
  }

  /**
   * @copydoc bitset::clear()
   */
  dense_bitset& clear() noexcept {
    _size = 0;
    _words.clear();
    return *this;
  }

  /**
   * @copydoc bitset::set()
   */
  dense_bitset& set() noexcept {
    // FIXME: implement a special case for the last word.
    std::fill(_words.begin(), _words.end(), static_cast<word_type>(-1));
    return *this;
  }

  /**
   * @copydoc bitset::set(std::size_t,bool)
   */
  dense_bitset& set(std::size_t pos, bool value = true) {
    throw std::out_of_range{"pos >= size()"}; // TODO
    return (void)pos, (void)value, *this;
  }

  /**
   * @copydoc bitset::reset()
   */
  dense_bitset& reset() noexcept {
    std::fill(_words.begin(), _words.end(), static_cast<word_type>(0));
    return *this;
  }

  /**
   * @copydoc bitset::reset(std::size_t)
   */
  dense_bitset& reset(std::size_t pos) {
    //assert(pos < size());
    return set(pos, false);
  }

  /**
   * @copydoc bitset::flip()
   */
  dense_bitset& flip() noexcept {
    // TODO
    return *this;
  }
};

#endif /* DRY_DENSE_BITSET_H */
