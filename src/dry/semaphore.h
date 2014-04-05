/* This is free and unencumbered software released into the public domain. */

#ifndef DRY_SEMAPHORE_H
#define DRY_SEMAPHORE_H

/**
 * @file
 */

namespace dry {
  class semaphore;
}

/**
 * A semaphore.
 *
 * @abstract
 * @see http://en.wikipedia.org/wiki/Semaphore_(programming)
 */
class dry::semaphore {
protected:
  /**
   * Default constructor.
   */
  semaphore() noexcept = default;

public:
  /**
   * Copy constructor.
   */
  semaphore(const semaphore& other) noexcept = default;

  /**
   * Move constructor.
   */
  semaphore(semaphore&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~semaphore() noexcept = default;

  /**
   * Copy assignment operator.
   */
  semaphore& operator=(const semaphore& other) noexcept = default;

  /**
   * Move assignment operator.
   */
  semaphore& operator=(semaphore&& other) noexcept = default;
};

#endif /* DRY_SEMAPHORE_H */
