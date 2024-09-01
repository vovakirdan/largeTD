CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
UI_DIR = $(SRC_DIR)/ui
PLATFORM_DIR = $(SRC_DIR)/platform
OBJ_DIR = build

# List of core source files
CORE_SRCS = $(CORE_DIR)/matrix.cpp $(CORE_DIR)/vector3d.cpp $(CORE_DIR)/mesh.cpp \
            $(CORE_DIR)/renderer.cpp $(CORE_DIR)/viewport.cpp $(CORE_DIR)/framebuffer.cpp \
            $(CORE_DIR)/camera.cpp

# List of UI source files
UI_SRCS = $(UI_DIR)/window.cpp $(UI_DIR)/event_handler.cpp $(UI_DIR)/ui_renderer.cpp \
          $(UI_DIR)/ui_manager.cpp

# Platform-specific source files (you can switch between different platforms)
PLATFORM_SRCS = $(PLATFORM_DIR)/windows/window_winapi.cpp $(PLATFORM_DIR)/windows/event_handler_winapi.cpp
# PLATFORM_SRCS = $(PLATFORM_DIR)/linux/window_x11.cpp $(PLATFORM_DIR)/linux/event_handler_x11.cpp

# Main application source
MAIN_SRCS = src/main.cpp

# Object files
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CORE_SRCS) $(UI_SRCS) $(PLATFORM_SRCS) $(MAIN_SRCS))

# Target executable
TARGET = renderer_app

# Rule to build the project
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)/core $(OBJ_DIR)/ui $(OBJ_DIR)/platform/windows $(OBJ_DIR)/platform/linux
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
