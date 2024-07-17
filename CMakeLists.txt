cmake_minimum_required(VERSION 3.27)
project(EISFELD_BRANT_PROJEKT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add project sources
file(GLOB_RECURSE SRC "*.cpp")
list(FILTER SRC EXCLUDE REGEX "build/")
list(FILTER SRC EXCLUDE REGEX "projektTest/")

# Fetch googletest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Find OpenCV
set(OpenCV_DIR "C:/opencv/build/install")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Debug messages
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Create a library from the shared source files
add_library(EISFELD_BRANT_PROJEKT_LIB ${SRC})
target_link_libraries(EISFELD_BRANT_PROJEKT_LIB ${OpenCV_LIBS})

# Define the main project executable
add_executable(EISFELD_BRANT_PROJEKT main.cpp)
target_link_libraries(EISFELD_BRANT_PROJEKT EISFELD_BRANT_PROJEKT_LIB)

# Add subdirectory for tests
add_subdirectory(projektTest)
