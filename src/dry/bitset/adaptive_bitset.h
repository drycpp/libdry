/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_ADAPTIVE_BITSET_H
#define DRY_ADAPTIVE_BITSET_H

/**
 * @file
 */

#include "../bitset.h"
#include "empty_bitset.h"
#include "dense_bitset.h"
#include "small_bitset.h"
#include "uniform_bitset.h"

#include <memory> /* for std::unique_ptr */

namespace dry {
  class adaptive_bitset;
}

/**
 * An adaptive bitset.
 */
class dry::adaptive_bitset final : public dry::bitset<adaptive_bitset> {
  struct interface;
  std::unique_ptr<interface> _impl;

public:
  /**
   * Default constructor.
   */
  adaptive_bitset()
    : _impl{new empty_implementation} {}

  /**
   * Constructor.
   */
  adaptive_bitset(std::size_t size)
    : _impl{new small_implementation{size}} {}

  /**
   * Copy constructor.
   */
  adaptive_bitset(const adaptive_bitset& other) = default;

  /**
   * Move constructor.
   */
  adaptive_bitset(adaptive_bitset&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~adaptive_bitset() noexcept = default;

  /**
   * Copy assignment operator.
   */
  adaptive_bitset& operator=(const adaptive_bitset& other) = default;

  /**
   * Move assignment operator.
   */
  adaptive_bitset& operator=(adaptive_bitset&& other) noexcept = default;

  /**
   * @copydoc bitset::empty()
   */
  bool empty() const noexcept {
    return size() == 0;
  }

  /**
   * @copydoc bitset::size()
   */
  std::size_t size() const noexcept {
    return _impl->size();
  }

  /**
   * @copydoc bitset::count()
   */
  std::size_t count(bool value = true) const noexcept {
    return _impl->count(value);
  }

  /**
   * @copydoc bitset::all()
   */
  bool all() const noexcept {
    return _impl->all();
  }

  /**
   * @copydoc bitset::any()
   */
  bool any() const noexcept {
    return _impl->any();
  }

  /**
   * @copydoc bitset::none()
   */
  bool none() const noexcept {
    return _impl->none();
  }

  /**
   * @copydoc bitset::test()
   */
  bool test(std::size_t pos) const {
    return _impl->test(pos);
  }

  /**
   * @copydoc bitset::operator[]()
   */
  bool operator[](std::size_t pos) const noexcept {
    return _impl->operator[](pos);
  }

  /**
   * @copydoc bitset::clear()
   */
  adaptive_bitset& clear() noexcept {
    return _impl->clear(), *this;
  }

  /**
   * @copydoc bitset::set()
   */
  adaptive_bitset& set() noexcept {
    return _impl->set(), *this;
  }

  /**
   * @copydoc bitset::set(std::size_t,bool)
   */
  adaptive_bitset& set(std::size_t pos, bool value = true) {
    return _impl->set(pos, value), *this;
  }

  /**
   * @copydoc bitset::reset()
   */
  adaptive_bitset& reset() noexcept {
    return _impl->reset(), *this;
  }

  /**
   * @copydoc bitset::reset(std::size_t)
   */
  adaptive_bitset& reset(std::size_t pos) {
    return set(pos, false);
  }

  /**
   * @copydoc bitset::flip()
   */
  adaptive_bitset& flip() noexcept {
    return _impl->flip(), *this;
  }

private:
  struct interface {
    virtual ~interface() noexcept = default;
    virtual std::size_t size() const noexcept = 0;
    virtual std::size_t count(bool value = true) const noexcept = 0;
    virtual bool all() const noexcept = 0;
    virtual bool any() const noexcept = 0;
    virtual bool none() const noexcept = 0;
    virtual bool test(std::size_t pos) const = 0;
    virtual bool operator[](std::size_t pos) const noexcept = 0;
    virtual void clear() noexcept = 0;
    virtual void set() noexcept = 0;
    virtual void set(std::size_t pos, bool value = true) = 0;
    virtual void reset() noexcept = 0;
    virtual void flip() noexcept = 0;
  };

  template <class Bitset>
  struct implementation : public interface {
    Bitset self;
    implementation() noexcept = default;
    implementation(std::size_t size) noexcept : self{size} {}
    virtual ~implementation() noexcept override = default;
    virtual std::size_t size() const noexcept override {
      return self.size();
    }
    virtual std::size_t count(bool value = true) const noexcept override {
      return self.count(value);
    }
    virtual bool all() const noexcept override {
      return self.all();
    }
    virtual bool any() const noexcept override {
      return self.any();
    }
    virtual bool none() const noexcept override {
      return self.none();
    }
    virtual bool test(std::size_t pos) const override {
      return self.test(pos);
    }
    virtual bool operator[](std::size_t pos) const noexcept override {
      return self.operator[](pos);
    }
    virtual void clear() noexcept override {
      self.clear();
    }
    virtual void set() noexcept override {
      self.set();
    }
    virtual void set(std::size_t pos, bool value = true) override {
      self.set(pos, value);
    }
    virtual void reset() noexcept override {
      self.reset();
    }
    virtual void flip() noexcept override {
      //self.flip();
    }
  };

  struct dense_implementation final : public implementation<dense_bitset> {
    dense_implementation(std::size_t size) noexcept
      : implementation<dense_bitset>{size} {}
  };

  struct empty_implementation final : public implementation<empty_bitset> {};

  struct small_implementation final : public implementation<small_bitset<>> {
    small_implementation(std::size_t size) noexcept
      : implementation<small_bitset<>>{size} {}
  };

  struct uniform_implementation final : public implementation<uniform_bitset> {
    uniform_implementation(std::size_t size) noexcept
      : implementation<uniform_bitset>{size} {}
  };
};

#endif /* DRY_ADAPTIVE_BITSET_H */
