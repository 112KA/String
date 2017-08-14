# BasicString
BasicString is a simple C++ string type that can be set memory allocator.This code consists of a single header file BasicString.hpp. 

## Integration
The single required source, file BasicString.hpp is in the src directory. All you need to do is add
```cpp
#include "BasicString.hpp"
```
Do not forget to set the necessary switches to enable C++11 (e.g., -std=c++11 for GCC and Clang).

## Example
```cpp


// use std::allocator 
using string = BasicString<char, std::char_traits<char>, std::allocator<char> >;
// or original allocator
using my_string = BasicString<char, std::char_traits<char>, my_allocator<char> >;




//constructor
my_string s1("string1");
printf("%s\n", s1.c_str());		//string1

my_string s2("string%d",2);
printf("%s\n", s2.c_str());		//string2

my_string s3(s1 + "_" + s2);
printf("%s\n", s3.c_str());		//string1_string2


//operator+=
s1 += "_";
s1 += s2;
s1 += "_" + s3;
printf("%s\n", s1.c_str());		//string1_string2_string1_string2


//append
s2.append("_string3");
s2.append("_string%d",4);
printf("%s\n", s2.c_str());		//string2_string3_string4


```