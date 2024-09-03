cmake_minimum_required(VERSION 3.10)

# Project name
project(largeTD)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common source files
set(SOURCES
    src/main.cpp
    src/core/camera.cpp
    src/core/framebuffer.cpp
    src/core/matrix.cpp
    src/core/mesh.cpp
    src/core/renderer.cpp
    src/core/vector3d.cpp
    src/core/viewport.cpp
    src/ui/event_handler.cpp
    src/ui/ui_manager.cpp
    src/ui/ui_renderer.cpp
    src/ui/window.cpp
)

# Platform-specific configurations
if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)

    # Include Windows SDK directories if provided
    if(DEFINED ENV{WINDOWS_SDK_INCLUDE_DIRS})
        include_directories($ENV{WINDOWS_SDK_INCLUDE_DIRS})
    endif()

    # Add Windows-specific source files
    list(APPEND SOURCES
        src/platform/windows/window_winapi.cpp
    )

    # Link against Windows libraries
    set(PLATFORM_LIBS user32 gdi32)

elseif(UNIX AND NOT APPLE)
    add_definitions(-DPLATFORM_LINUX)

    # Add Linux-specific source files
    list(APPEND SOURCES
        src/platform/linux/window_x11.cpp
    )

    # Find and link against X11
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    set(PLATFORM_LIBS ${X11_LIBRARIES})
endif()

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Specify include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# Link necessary libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LIBS})

# Optionally set output directories
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
