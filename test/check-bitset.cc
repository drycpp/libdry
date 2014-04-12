/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <dry/bitset.h>
#include <dry/bitset/empty_bitset.h>
#include <dry/bitset/small_bitset.h>
#include <dry/bitset/uniform_bitset.h>

////////////////////////////////////////////////////////////////////////////////
/* dry::bitset */

using bitset = dry::empty_bitset;

TEST_CASE("bitset::npos") {
  REQUIRE(bitset::npos > 0);
}

TEST_CASE("bitset::word_size") {
  REQUIRE(bitset::word_size > 0);
}

////////////////////////////////////////////////////////////////////////////////
/* dry::empty_bitset */

using empty_bitset = dry::empty_bitset;

TEST_CASE("empty_bitset#size") {
  REQUIRE(empty_bitset{}.size() == 0);
}

TEST_CASE("empty_bitset#flip") {
  REQUIRE_NOTHROW(empty_bitset{}.flip());
}

////////////////////////////////////////////////////////////////////////////////
/* dry::small_bitset */

using small_bitset = dry::small_bitset<16>;

TEST_CASE("small_bitset#size") {
  REQUIRE(small_bitset{}.size() == 0);
}

TEST_CASE("small_bitset#flip") {
  REQUIRE_NOTHROW(small_bitset{}.flip());
}

////////////////////////////////////////////////////////////////////////////////
/* dry::uniform_bitset */

using uniform_bitset = dry::uniform_bitset;

TEST_CASE("uniform_bitset#size") {
  REQUIRE(uniform_bitset{}.size() == 0);
}

TEST_CASE("uniform_bitset#flip") {
  REQUIRE_NOTHROW(uniform_bitset{}.flip());
}
