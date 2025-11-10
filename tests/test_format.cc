
#include <catch2/catch_test_macros.hpp>

#include "QFString.h"

TEST_CASE("Comprehensive Test") {
    {
        // emptiness test
        QFString<32> empty_str32;
        REQUIRE(empty_str32.capacity() == 31ull);
        REQUIRE(empty_str32.size() == 0ull);
    }

    {
        QFString<32> str32;
        str32.format("my name is... %s", "Andrew");
        REQUIRE(str32.string() == std::string("my name is... Andrew"));

        // copy constructor
        auto str32_copy(str32);
        REQUIRE(str32_copy.string() == std::string("my name is... Andrew"));

        // move constructor (in this case, there is no moving, just copying (buffer is stack allocated))
        auto str32_move(std::move(str32));
        REQUIRE(str32_move.string() == std::string("my name is... Andrew"));
    }

    {
        QFString<32> str32;
        str32.format("The year is %d", 2025);
        REQUIRE(str32.string() == std::string("The year is 2025"));

        // copy assignment
        auto str32_copy_asgn = str32;
        REQUIRE(str32_copy_asgn.string() == std::string("The year is 2025"));

        // move assignment
        auto str32_move_asgn = std::move(str32);
        REQUIRE(str32_move_asgn.string() == std::string("The year is 2025"));
    }

    {
        // equality test
        auto equality_test = QFString<32>().format("%02i + %02i = %02i", 40, 2, 42);

        REQUIRE(equality_test == "40 + 02 = 42");
        REQUIRE(equality_test == std::string("40 + 02 = 42"));
        REQUIRE(equality_test == QFString<32>().format("%02i + %02i = %02i", 40, 2, 42));
    }

    {
        // test that the buffer is not overflown (buffer is not overflown)
        QFString<8> buffer_overflow_test;
        buffer_overflow_test.format("%d + %d is %d", 1, 2, 3);
        REQUIRE(buffer_overflow_test.size() < 8);
        REQUIRE(buffer_overflow_test == "1 + 2 i");
    }
}