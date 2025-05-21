#include "catch2/catch.hpp"
#include "math/math.hpp"


TEST_CASE( "Addition tests", "[add]" ) {
    REQUIRE( addition(9, 11) == 20 );
    REQUIRE( addition(2, 21) == 23 );
}