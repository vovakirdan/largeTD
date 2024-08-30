cmake_minimum_required(VERSION 3.10)
project(LARGETD)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES src/*.cpp)

# Main executable
add_executable(LARGETD main.cpp ${SOURCES})

# Test executables
add_executable(test_matrix_and_vector tests/test_matrix_and_vector.cpp ${SOURCES})
add_executable(test_mesh tests/test_mesh.cpp ${SOURCES})
add_executable(test_vector3d tests/test_vector3d.cpp ${SOURCES})

# Enable testing
enable_testing()
add_test(NAME MatrixAndVectorTests COMMAND test_matrix_and_vector)
add_test(NAME MeshTests COMMAND test_mesh)
add_test(NAME Vector3DTests COMMAND test_vector3d)
