#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE( "Test integration ", "[add]" ) {
    REQUIRE( (9 + 11) == 20 );
    REQUIRE( (2 + 21) == 23 );
}