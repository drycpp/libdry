/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <dry/bitops.h>

using namespace dry;

TEST_CASE("popcount64()") {
  REQUIRE(popcount64(0b0) == 0);
  REQUIRE(popcount64(0b1) == 1);
  REQUIRE(popcount64(0b11) == 2);
  REQUIRE(popcount64(0b111) == 3);
  REQUIRE(popcount64(0b100) == 1);
  REQUIRE(popcount64(~0ULL) == 64);
}
