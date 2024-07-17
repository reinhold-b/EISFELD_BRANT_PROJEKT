cmake_minimum_required(VERSION 3.27)
project(projektTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE TEST_SRC "*.cpp")

# Include FetchContent to get GoogleTest if not already available
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add the test executable
add_executable(${PROJECT_NAME} ${TEST_SRC})

# Include directories for gtest
target_include_directories(${PROJECT_NAME} PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Link against gtest, gtest_main, and the shared library
target_link_libraries(${PROJECT_NAME} gtest gtest_main EISFELD_BRANT_PROJEKT_LIB)

# Add the test to CTest
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
