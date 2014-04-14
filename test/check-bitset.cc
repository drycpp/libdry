/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <dry/bitset.h>
#include <dry/bitset/adaptive_bitset.h>
#include <dry/bitset/dense_bitset.h>
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
/* dry::dense_bitset */

using dense_bitset = dry::dense_bitset;

TEST_CASE("dense_bitset#size") {
  REQUIRE(dense_bitset{}.size() == 0);
  REQUIRE(dense_bitset{1}.size() == 1);
  REQUIRE(dense_bitset{100}.size() == 100);
  REQUIRE_NOTHROW(dense_bitset{1ULL<<33}.size());
}

TEST_CASE("dense_bitset#all") {
  REQUIRE(dense_bitset{}.all() == false);
  REQUIRE(dense_bitset{1}.all() == false);
#if 0
  REQUIRE(dense_bitset{1}.set(0).all() == true);
  REQUIRE(dense_bitset{2}.set(0).all() == false);
  REQUIRE(dense_bitset{2}.set(1).all() == false);
#endif
}

TEST_CASE("dense_bitset#any") {
  REQUIRE(dense_bitset{}.any() == false);
  REQUIRE(dense_bitset{1}.any() == false);
#if 0
  REQUIRE(dense_bitset{1}.set(0).any() == true);
  REQUIRE(dense_bitset{2}.set(0).any() == true);
  REQUIRE(dense_bitset{2}.set(1).any() == true);
#endif
}

TEST_CASE("dense_bitset#none") {
  REQUIRE(dense_bitset{}.none() == true);
  REQUIRE(dense_bitset{1}.none() == true);
#if 0
  REQUIRE(dense_bitset{1}.set(0).none() == false);
  REQUIRE(dense_bitset{2}.set(0).none() == false);
  REQUIRE(dense_bitset{2}.set(1).none() == false);
#endif
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

TEST_CASE("empty_bitset#all") {
  REQUIRE(empty_bitset{}.all() == false);
}

TEST_CASE("empty_bitset#any") {
  REQUIRE(empty_bitset{}.any() == false);
}

TEST_CASE("empty_bitset#none") {
  REQUIRE(empty_bitset{}.none() == true);
}

TEST_CASE("empty_bitset#test") {
  REQUIRE_THROWS_AS(empty_bitset{}.test(0), std::out_of_range);
}

TEST_CASE("empty_bitset#set") {
  REQUIRE_NOTHROW(empty_bitset{}.set());
}

TEST_CASE("empty_bitset#set(pos)") {
  REQUIRE_THROWS_AS(empty_bitset{}.set(0), std::out_of_range);
}

TEST_CASE("empty_bitset#reset") {
  REQUIRE_NOTHROW(empty_bitset{}.reset());
}

TEST_CASE("empty_bitset#reset(pos)") {
  REQUIRE_THROWS_AS(empty_bitset{}.reset(0), std::out_of_range);
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

TEST_CASE("small_bitset#all") {
  REQUIRE(small_bitset{}.all() == false);
  REQUIRE(small_bitset{1}.all() == false);
  REQUIRE(small_bitset{1}.set(0).all() == true);
  REQUIRE(small_bitset{2}.set(0).all() == false);
  REQUIRE(small_bitset{2}.set(1).all() == false);
}

TEST_CASE("small_bitset#any") {
  REQUIRE(small_bitset{}.any() == false);
  REQUIRE(small_bitset{1}.any() == false);
  REQUIRE(small_bitset{1}.set(0).any() == true);
  REQUIRE(small_bitset{2}.set(0).any() == true);
  REQUIRE(small_bitset{2}.set(1).any() == true);
}

TEST_CASE("small_bitset#none") {
  REQUIRE(small_bitset{}.none() == true);
  REQUIRE(small_bitset{1}.none() == true);
  REQUIRE(small_bitset{1}.set(0).none() == false);
  REQUIRE(small_bitset{2}.set(0).none() == false);
  REQUIRE(small_bitset{2}.set(1).none() == false);
}

TEST_CASE("small_bitset#test") {
  REQUIRE_THROWS_AS(small_bitset{}.test(0), std::out_of_range);
  REQUIRE(small_bitset{1}.test(0) == false);
  REQUIRE(small_bitset{1}.set(0).test(0) == true);
  REQUIRE(small_bitset{2}.set(0).test(0) == true);
  REQUIRE(small_bitset{2}.set(1).test(1) == true);
}

TEST_CASE("small_bitset#set") {
  for (auto size = 0U; size < 16; size++) {
    small_bitset bits{size};
    bits.set();
    for (auto pos = 0U; pos < size; pos++) {
      REQUIRE(bits.test(pos) == true);
    }
  }
  REQUIRE_THROWS_AS(small_bitset{16}.set(), std::domain_error);
}

TEST_CASE("small_bitset#set(pos)") {
  REQUIRE_THROWS_AS(small_bitset{}.set(0), std::out_of_range);
  REQUIRE(small_bitset{1}.reset().set(0).test(0) == true);
}

TEST_CASE("small_bitset#reset") {
  for (auto size = 0U; size < 16; size++) {
    small_bitset bits{size};
    bits.set().reset();
    for (auto pos = 0U; pos < size; pos++) {
      REQUIRE(bits.test(pos) == false);
    }
  }
  REQUIRE_NOTHROW(small_bitset{16}.reset());
}

TEST_CASE("small_bitset#reset(pos)") {
  REQUIRE_THROWS_AS(small_bitset{}.reset(0), std::out_of_range);
  REQUIRE(small_bitset{1}.set().reset(0).test(0) == false);
  REQUIRE(small_bitset{2}.set().reset(0).test(1) == true);
  REQUIRE(small_bitset{3}.set().reset(0).count() == 2);
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

TEST_CASE("uniform_bitset#all") {
  REQUIRE(uniform_bitset{}.all() == false);
  REQUIRE(uniform_bitset(1, false).all() == false);
  REQUIRE(uniform_bitset(1, true).all() == true);
}

TEST_CASE("uniform_bitset#any") {
  REQUIRE(uniform_bitset{}.any() == false);
  REQUIRE(uniform_bitset(1, false).any() == false);
  REQUIRE(uniform_bitset(1, true).any() == true);
}

TEST_CASE("uniform_bitset#none") {
  REQUIRE(uniform_bitset{}.none() == true);
  REQUIRE(uniform_bitset(1, false).none() == true);
  REQUIRE(uniform_bitset(1, true).none() == false);
}

TEST_CASE("uniform_bitset#test") {
  REQUIRE_THROWS_AS(uniform_bitset{}.test(0), std::out_of_range);
  REQUIRE(uniform_bitset(1, false).test(0) == false);
  REQUIRE(uniform_bitset(1, true).test(0) == true);
}

TEST_CASE("uniform_bitset#set") {
  REQUIRE(uniform_bitset{}.set().value() == true);
}

TEST_CASE("uniform_bitset#set(pos)") {
  REQUIRE_THROWS_AS(uniform_bitset{}.set(0), std::out_of_range);
  REQUIRE_THROWS_AS(uniform_bitset(1, false).set(0), std::logic_error);
  REQUIRE_NOTHROW(uniform_bitset(1, true).set(0));
}

TEST_CASE("uniform_bitset#reset") {
  REQUIRE(uniform_bitset{}.reset().value() == false);
}

TEST_CASE("uniform_bitset#reset(pos)") {
  REQUIRE_THROWS_AS(uniform_bitset{}.reset(0), std::out_of_range);
  REQUIRE_THROWS_AS(uniform_bitset(1, true).reset(0), std::logic_error);
  REQUIRE_NOTHROW(uniform_bitset(1, false).reset(0));
}

TEST_CASE("uniform_bitset#flip") {
  REQUIRE_NOTHROW(uniform_bitset{}.flip());
  REQUIRE(uniform_bitset{}.value() == false);
  REQUIRE(uniform_bitset{}.flip().value() == true);
}

////////////////////////////////////////////////////////////////////////////////
/* dry::adaptive_bitset */

using adaptive_bitset = dry::adaptive_bitset;

TEST_CASE("adaptive_bitset#size") {
  REQUIRE(adaptive_bitset{}.size() == 0);
  REQUIRE(adaptive_bitset{1}.size() == 1);
  REQUIRE(adaptive_bitset{100}.size() == 100);
  REQUIRE(adaptive_bitset{4096}.size() == 4096);
}

TEST_CASE("adaptive_bitset#count") {
  REQUIRE(adaptive_bitset{}.count(true) == 0);
  REQUIRE(adaptive_bitset{}.count(false) == 0);
  REQUIRE(adaptive_bitset{1}.count(true) == 0);
  REQUIRE(adaptive_bitset{1}.count(false) == 1);
}

TEST_CASE("adaptive_bitset#all") {
  REQUIRE(adaptive_bitset{}.all() == false);
  REQUIRE(adaptive_bitset{1}.all() == false);
  REQUIRE(adaptive_bitset{1}.set(0).all() == true);
  REQUIRE(adaptive_bitset{2}.set(0).all() == false);
  REQUIRE(adaptive_bitset{2}.set(1).all() == false);
}

TEST_CASE("adaptive_bitset#any") {
  REQUIRE(adaptive_bitset{}.any() == false);
  REQUIRE(adaptive_bitset{1}.any() == false);
  REQUIRE(adaptive_bitset{1}.set(0).any() == true);
  REQUIRE(adaptive_bitset{2}.set(0).any() == true);
  REQUIRE(adaptive_bitset{2}.set(1).any() == true);
}

TEST_CASE("adaptive_bitset#none") {
  REQUIRE(adaptive_bitset{}.none() == true);
  REQUIRE(adaptive_bitset{1}.none() == true);
  REQUIRE(adaptive_bitset{1}.set(0).none() == false);
  REQUIRE(adaptive_bitset{2}.set(0).none() == false);
  REQUIRE(adaptive_bitset{2}.set(1).none() == false);
}

TEST_CASE("adaptive_bitset#test") {
  REQUIRE_THROWS_AS(adaptive_bitset{}.test(0), std::out_of_range);
  REQUIRE(adaptive_bitset{1}.test(0) == false);
  REQUIRE(adaptive_bitset{1}.set(0).test(0) == true);
  REQUIRE(adaptive_bitset{2}.set(0).test(0) == true);
  REQUIRE(adaptive_bitset{2}.set(1).test(1) == true);
}

TEST_CASE("adaptive_bitset#set") {
  for (auto size = 0U; size < 16; size++) {
    adaptive_bitset bits{size};
    bits.set();
    for (auto pos = 0U; pos < size; pos++) {
      REQUIRE(bits.test(pos) == true);
    }
  }
}

TEST_CASE("adaptive_bitset#set(pos)") {
  REQUIRE_THROWS_AS(adaptive_bitset{}.set(0), std::out_of_range);
  REQUIRE(adaptive_bitset{1}.reset().set(0).test(0) == true);
}

TEST_CASE("adaptive_bitset#reset") {
  for (auto size = 0U; size < 16; size++) {
    adaptive_bitset bits{size};
    bits.set().reset();
    for (auto pos = 0U; pos < size; pos++) {
      REQUIRE(bits.test(pos) == false);
    }
  }
  REQUIRE_NOTHROW(adaptive_bitset{16}.reset());
}

TEST_CASE("adaptive_bitset#reset(pos)") {
  REQUIRE_THROWS_AS(adaptive_bitset{}.reset(0), std::out_of_range);
  REQUIRE(adaptive_bitset{1}.set().reset(0).test(0) == false);
  REQUIRE(adaptive_bitset{2}.set().reset(0).test(1) == true);
  REQUIRE(adaptive_bitset{3}.set().reset(0).count() == 2);
}

TEST_CASE("adaptive_bitset#flip") {
  // TODO
}
