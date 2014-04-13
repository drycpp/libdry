/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_ATOMIC_BINARY_SEMAPHORE_H
#define DRY_ATOMIC_BINARY_SEMAPHORE_H

/**
 * @file
 */

#include "../semaphore.h"

#include <atomic> /* for std::atomic_flag */

namespace dry {
  class atomic_binary_semaphore;
}

/**
 * An atomic binary semaphore.
 *
 * @note Instances of this class are neither movable nor copyable.
 */
class dry::atomic_binary_semaphore final : public dry::binary_semaphore {
  std::atomic_flag _state {ATOMIC_FLAG_INIT};

public:
  /**
   * Default constructor.
   */
  atomic_binary_semaphore() noexcept = default;

  /**
   * Copy constructor.
   */
  atomic_binary_semaphore(const atomic_binary_semaphore& other) noexcept = delete;

  /**
   * Move constructor.
   */
  atomic_binary_semaphore(atomic_binary_semaphore&& other) noexcept = delete;

  /**
   * Destructor.
   */
  ~atomic_binary_semaphore() noexcept = default;

  /**
   * Copy assignment operator.
   */
  atomic_binary_semaphore& operator=(const atomic_binary_semaphore& other) noexcept = delete;

  /**
   * Move assignment operator.
   */
  atomic_binary_semaphore& operator=(atomic_binary_semaphore&& other) noexcept = delete;

  /**
   * ...
   */
  void wait() noexcept {
    while (_state.test_and_set()) {} /* spin loop */
  }

  /**
   * ...
   */
  void notify() noexcept {
    _state.clear();
  }
};

#endif /* DRY_ATOMIC_BINARY_SEMAPHORE_H */
