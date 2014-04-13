/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <dry/semaphore.h>
#include <dry/semaphore/atomic_binary_semaphore.h>

#include <mutex> /* for std::lock_guard */

////////////////////////////////////////////////////////////////////////////////
/* dry::atomic_binary_semaphore */

using atomic_binary_semaphore = dry::atomic_binary_semaphore;

TEST_CASE("atomic_binary_semaphore") {
  // TODO
}

TEST_CASE("atomic_binary_semaphore#wait") {
  atomic_binary_semaphore sem{false}; /* don't block on #wait() */
  REQUIRE_NOTHROW(sem.wait());
}

TEST_CASE("atomic_binary_semaphore#notify") {
  atomic_binary_semaphore sem;
  REQUIRE_NOTHROW(sem.notify());
}

#if 0
TEST_CASE("atomic_binary_semaphore with std::lock_guard") {
  atomic_binary_semaphore sem;
  std::lock_guard<atomic_binary_semaphore> lock{sem};
}
#endif
