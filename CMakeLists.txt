cmake_minimum_required(VERSION 3.10)

# Project name
project(largeTD)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include src)

# Platform-specific include directories
if(WIN32)
    include_directories($ENV{WINDOWS_SDK_INCLUDE_DIRS})
endif()

# Source files
set(SOURCES
        src/main.cpp
        src/core/camera.cpp
        src/core/framebuffer.cpp
        src/core/matrix.cpp
        src/core/mesh.cpp
        src/core/renderer.cpp
        src/core/vector3d.cpp
        src/core/viewport.cpp
        src/platform/windows/window_winapi.cpp
        src/platform/linux/window_x11.cpp
        src/ui/event_handler.cpp
        src/ui/ui_manager.cpp
        src/ui/ui_renderer.cpp
        src/ui/window.cpp
)

# Header files (not strictly necessary to list them all, but useful for IDEs)
set(HEADERS
        src/core/camera.hpp
        src/core/Config.hpp
        src/core/framebuffer.hpp
        src/core/matrix.hpp
        src/core/mesh.hpp
        src/core/renderer.hpp
        src/core/vector3d.hpp
        src/core/viewport.hpp
        src/platform/windows/window_winapi.hpp
        src/platform/linux/window_x11.hpp
        src/ui/event_handler.hpp
        src/ui/ui_manager.hpp
        src/ui/ui_renderer.hpp
        src/ui/window.hpp
)

# Platform-specific configurations
if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
    list(APPEND SOURCES src/platform/windows/window_winapi.cpp)
    list(APPEND HEADERS src/platform/windows/window_winapi.hpp)

    # Ensure the Windows API is available
    find_package(WindowsSDK REQUIRED)
elseif(UNIX AND NOT APPLE)
    add_definitions(-DPLATFORM_LINUX)
    list(APPEND SOURCES src/platform/linux/window_x11.cpp)
    list(APPEND HEADERS src/platform/linux/window_x11.hpp)
endif()

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link necessary libraries (adjust according to your project needs)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} user32 gdi32)
endif()

# Optionally set output directories
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
