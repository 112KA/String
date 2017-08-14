#include "catch.hpp"
#include "BasicString.hpp"


TEST_CASE( "capacity" ) {

    using _Allocator = std::allocator<char>;
    using string = BasicString<char, std::char_traits<char>, _Allocator >;

    string s("capacity test");

    SECTION("size") {
    	REQUIRE(s.size()==13);
    	REQUIRE(s.length()==13);
    }

    SECTION("clear") {
    	s.clear();
    	REQUIRE(s.size()==0);
	    REQUIRE_THAT("", Catch::Equals(s.c_str()));
    }

    SECTION("empty") {
    	REQUIRE_FALSE(s.empty());
    	s.clear();
    	REQUIRE(s.empty());
    }
}