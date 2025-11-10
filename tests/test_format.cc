
#include <catch2/catch_test_macros.hpp>

#include "QFString.h"

using QFString16 = QFString<16, char>;

TEST_CASE("32 Character Formatting Test") {
    REQUIRE(QFString<32>().format("%02i + %02i = %02i", 40, 2, 42).string() == std::string("40 + 02 = 42"));
}