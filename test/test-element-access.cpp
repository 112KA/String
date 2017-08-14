#include "catch.hpp"
#include "BasicString.hpp"


TEST_CASE( "element access" ) {

    using _Allocator = std::allocator<char>;
    using string = BasicString<char, std::char_traits<char>, _Allocator >;

    string s("test1");

    SECTION("operator[]") {
    	string s0("%c", s[0]);
    	string s1("%c", s[1]);
	    REQUIRE_THAT("t", Catch::Equals(s0.c_str()));
	    REQUIRE_THAT("e", Catch::Equals(s1.c_str()));
    }

    SECTION("at") {
    	string s0("%c", s.at(0));
    	string s1("%c", s.at(1));
	    REQUIRE_THAT("t", Catch::Equals(s0.c_str()));
	    REQUIRE_THAT("e", Catch::Equals(s1.c_str()));
    }
}