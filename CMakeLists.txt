cmake_minimum_required(VERSION 3.10)
project(LARGETD)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Main executable target
add_executable(LARGETD main.cpp ${SOURCES})

# Test executable for running all tests
add_executable(tests tests/all_tests.cpp ${SOURCES})

# Enable testing
enable_testing()
add_test(NAME AllTests COMMAND tests)
