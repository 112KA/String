cmake_minimum_required(VERSION 3.7.2)

# define the project
project(BasicString VERSION 1.0.0 LANGUAGES CXX)

add_definitions("-Wall -std=c++11")

include_directories(src)

add_subdirectory(docs)

option(utest "Build the unit tests" ON)

if(utest)
	add_subdirectory(test)
endif()
