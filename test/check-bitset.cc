/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <dry/bitset.h>

using namespace dry;

namespace {
  class dynamic_bitset : public dry::bitset<dynamic_bitset, std::uint64_t> {};
}

TEST_CASE("bitset::npos") {
  REQUIRE(dynamic_bitset::npos > 0);
}

TEST_CASE("bitset::word_size") {
  REQUIRE(dynamic_bitset::word_size > 0);
}
