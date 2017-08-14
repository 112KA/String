# ref) https://github.com/philsquared/Catch/blob/master/docs/build-systems.md

enable_testing(true)  # Enables unit-testing.

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    catch
    PREFIX ${CMAKE_BINARY_DIR}/catch
    GIT_REPOSITORY https://github.com/philsquared/Catch.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
   )

# Expose required variable (CATCH_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(catch source_dir)
set(CATCH_INCLUDE_DIR ${source_dir}/single_include CACHE INTERNAL "Path to include folder for Catch")

add_library(catch_main OBJECT
    "tests-main.cpp"
)
target_include_directories(catch_main PRIVATE  ${CATCH_INCLUDE_DIR})

add_executable(Test
 $<TARGET_OBJECTS:catch_main>
 test-allocator.cpp
 test-construct.cpp
 test-capacity.cpp
 test-element-access.cpp
 test-modifiers.cpp
 test-string-operations.cpp
 )

# Includes Catch in the project:
target_include_directories(Test PRIVATE  ${CATCH_INCLUDE_DIR})

add_test(TestRuns Test)