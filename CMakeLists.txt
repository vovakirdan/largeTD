cmake_minimum_required(VERSION 3.1)

project(renderer_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(${CMAKE_SOURCE_DIR}/usr/include/X11)

set(SRCS
        src/core/matrix.cpp
        src/core/vector3d.cpp
        src/core/mesh.cpp
        src/core/renderer.cpp
        src/core/viewport.cpp
        src/core/framebuffer.cpp
        src/core/camera.cpp
        src/ui/window.cpp
        src/ui/event_handler.cpp
        src/ui/ui_renderer.cpp
        src/ui/ui_manager.cpp
)

if (WIN32)
    list(APPEND SRCS
            src/platform/windows/window_winapi.cpp
    )
else ()
    list(APPEND SRCS
            src/platform/linux/window_x11.cpp
    )
endif ()

add_executable(${PROJECT_NAME} ${SRCS})