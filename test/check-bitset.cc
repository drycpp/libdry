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

TEST_CASE("empty_bitset#count") {
  REQUIRE(empty_bitset{}.count(true) == 0);
  REQUIRE(empty_bitset{}.count(false) == 0);
}

TEST_CASE("empty_bitset#flip") {
  REQUIRE_NOTHROW(empty_bitset{}.flip());
}

////////////////////////////////////////////////////////////////////////////////
/* dry::small_bitset */

using small_bitset = dry::small_bitset<16>;

TEST_CASE("small_bitset#size") {
  REQUIRE(small_bitset{}.size() == 0);
  REQUIRE(small_bitset{1}.size() == 1);
  REQUIRE(small_bitset{100}.size() == 100);
  REQUIRE_THROWS_AS(small_bitset{1ULL<<33}.size(), std::out_of_range);
}

TEST_CASE("small_bitset#count") {
  REQUIRE(small_bitset{}.count(true) == 0);
  REQUIRE(small_bitset{}.count(false) == 0);
  REQUIRE(small_bitset{1}.count(true) == 0);
  REQUIRE(small_bitset{1}.count(false) == 1);
}

TEST_CASE("small_bitset#flip") {} /* not supported */

////////////////////////////////////////////////////////////////////////////////
/* dry::uniform_bitset */

using uniform_bitset = dry::uniform_bitset;

TEST_CASE("uniform_bitset#size") {
  REQUIRE(uniform_bitset{}.size() == 0);
}

TEST_CASE("uniform_bitset#count") {
  REQUIRE(uniform_bitset{}.count(true) == 0);
  REQUIRE(uniform_bitset{}.count(false) == 0);
  REQUIRE(uniform_bitset{1}.count(true) == 0);
  REQUIRE(uniform_bitset{1}.count(false) == 1);
}

TEST_CASE("uniform_bitset#flip") {
  REQUIRE_NOTHROW(uniform_bitset{}.flip());
  REQUIRE(uniform_bitset{}.value() == false);
  REQUIRE(uniform_bitset{}.flip().value() == true);
}
