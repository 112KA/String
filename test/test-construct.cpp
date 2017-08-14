#include "catch.hpp"
#include "BasicString.hpp"


TEST_CASE( "construct" ) {

    using _Allocator = std::allocator<char>;
    using string = BasicString<char, std::char_traits<char>, _Allocator >;

    SECTION("constructor") {
    
	    SECTION( "no parameter" ) {
	    	string s;
	    	REQUIRE_THAT("", Catch::Equals(s.c_str()));
	    }

	    SECTION( "nullptr" ) {
	    	string s(nullptr);
	    	REQUIRE_THAT("", Catch::Equals(s.c_str()));
	    }

	    SECTION( "empty" ) {
	    	string s("");
	    	REQUIRE_THAT("", Catch::Equals(s.c_str()));
	    }

	    SECTION( "const char *" ) {
	    	string s("const char *");
	    	REQUIRE_THAT("const char *", Catch::Equals(s.c_str()));
	    }

	    SECTION( "format string" ) {
	    	string s("format%d", 1);
	    	REQUIRE_THAT("format1", Catch::Equals(s.c_str()));
	    }

	    SECTION( "reference" ) {
	    	string s("reference");
	    	string s2(s);
	    	REQUIRE_THAT("reference", Catch::Equals(s2.c_str()));
	    }
	}


    SECTION("operator=") {

	    SECTION( "nullptr" ) {
	    	string s;
	    	s = nullptr;
	    	REQUIRE_THAT("", Catch::Equals(s.c_str()));
	    }

	    SECTION( "empty" ) {
	    	string s;
	    	s = "";
	    	REQUIRE_THAT("", Catch::Equals(s.c_str()));
	    }

	    SECTION( "const char *" ) {
	    	string s;
	    	s = "const char *";
	    	REQUIRE_THAT("const char *", Catch::Equals(s.c_str()));
	    }

	    SECTION( "reference" ) {
	    	string s("reference");
	    	string s2;
	    	s2 = s;
	    	REQUIRE_THAT("reference", Catch::Equals(s2.c_str()));
	    }
    }
}