#include "catch.hpp"
#include "BasicString.hpp"


TEST_CASE( "string operations" ) {

    using _Allocator = std::allocator<char>;
    using string = BasicString<char, std::char_traits<char>, _Allocator >;

    unsigned long npos = string::npos;

    string s("test");

    SECTION("find") {
    	REQUIRE(s.find("es")==1);
    	REQUIRE(s.find("aes")==npos);
    	REQUIRE(s.find("esa")==npos);
    }

    SECTION("substr") {
        string s2;
        s2 = s.substr(2,1);
        REQUIRE_THAT("s", Catch::Equals(s2.c_str()));
        s2 = s.substr(2,2);
        REQUIRE_THAT("st", Catch::Equals(s2.c_str()));
        s2 = s.substr(2);
        REQUIRE_THAT("st", Catch::Equals(s2.c_str()));
        s2 = s.substr(3,4);
        REQUIRE_THAT("t", Catch::Equals(s2.c_str()));
    }

    SECTION("compare") {
        REQUIRE(s.compare("test")==0);

        REQUIRE(s.compare("test2")!=0);

        string s2("test");
        REQUIRE(s.compare(s2)==0);

        string s3("test2");
        REQUIRE(s.compare(s3)!=0);
    }

    SECTION("operator==") {
        REQUIRE(s == "test");
        string s2("test");
        REQUIRE(s == s2);
        REQUIRE(s != "test3");
        string s3("test2");
        REQUIRE(s != s3);
    }

    SECTION("operator+") {
        string s2 = s + "2";
        REQUIRE_THAT("test2", Catch::Equals(s2.c_str()));
        string s3("_test3");
        s2 = s + s3;
        REQUIRE_THAT("test_test3", Catch::Equals(s2.c_str()));
        string s4(s + "2" + s3);
        REQUIRE_THAT("test2_test3", Catch::Equals(s4.c_str()));

        s4 += "_test" "4";
        REQUIRE_THAT("test2_test3_test4", Catch::Equals(s4.c_str()));

//constructor
string ss1("string1");
printf("%s\n",ss1.c_str());     //string1

string ss2("string%d",2);
printf("%s\n",ss2.c_str());     //string2

string ss3(ss1 + "_" + ss2);
printf("%s\n",ss3.c_str());     //string1_string2

//operator+=
ss1 += "_";
ss1 += ss2;
ss1 += "_" + ss3;
printf("%s\n",ss1.c_str());     //string1_string2_string1_string2

//append
ss2.append("_string3");
ss2.append("_string%d",4);
printf("%s\n",ss2.c_str());     //string2_string3_string4
    }
}