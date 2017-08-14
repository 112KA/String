#include "catch.hpp"
#include "BasicString.hpp"


TEST_CASE( "modifiers" ) {

    using _Allocator = std::allocator<char>;
    using string = BasicString<char, std::char_traits<char>, _Allocator >;

    string s("test");

    SECTION("operator+=") {

    	SECTION("const char *") {
    		s += "1";
	    	REQUIRE_THAT("test1", Catch::Equals(s.c_str()));
    	}

    	SECTION("reference") {
    		string reference("1");
    		s += reference;
	    	REQUIRE_THAT("test1", Catch::Equals(s.c_str()));
    	}
    }

    SECTION("append") {

    	SECTION("const char *") {
    		s.append("1");
	    	REQUIRE_THAT("test1", Catch::Equals(s.c_str()));
    	}

    	SECTION("format string") {
    		s.append("%d", 1);
	    	REQUIRE_THAT("test1", Catch::Equals(s.c_str()));
    	}

    	SECTION("reference") {
    		string reference("1");
    		s.append(reference);
	    	REQUIRE_THAT("test1", Catch::Equals(s.c_str()));
    	}
    }

    SECTION("insert") {

    	SECTION("const char *") {
    		s.insert(2, ", insert check, ");
	    	REQUIRE_THAT("te, insert check, st", Catch::Equals(s.c_str()));
    	}

    	SECTION("format string") {
    		s.insert(2, ", insert %s, ", "check");
	    	REQUIRE_THAT("te, insert check, st", Catch::Equals(s.c_str()));
    	}

    	SECTION("reference") {
    		string reference(", insert check, ");
    		s.insert(2, reference);
	    	REQUIRE_THAT("te, insert check, st", Catch::Equals(s.c_str()));
    	}
    }

    SECTION("erase") {

    	SECTION("within range") {
    		s.erase(1, 2);
	    	REQUIRE_THAT("tt", Catch::Equals(s.c_str()));
    	}

    	SECTION("specified range is long") {
    		s.erase(1, 20);
	    	REQUIRE_THAT("t", Catch::Equals(s.c_str()));
    	}
    }
}