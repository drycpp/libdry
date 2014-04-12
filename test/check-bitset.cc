/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <dry/bitset.h>
#include <dry/bitset/empty_bitset.h>
#include <dry/bitset/uniform_bitset.h>

using namespace dry;

TEST_CASE("bitset::npos") {
  REQUIRE(empty_bitset::npos > 0);
}

TEST_CASE("bitset::word_size") {
  REQUIRE(empty_bitset::word_size > 0);
}

////////////////////////////////////////////////////////////////////////////////
/* dry::empty_bitset */

TEST_CASE("empty_bitset#size") {
  REQUIRE(empty_bitset{}.size() == 0);
}

////////////////////////////////////////////////////////////////////////////////
/* dry::uniform_bitset */

TEST_CASE("uniform_bitset#size") {
  REQUIRE(uniform_bitset{}.size() == 0);
}
