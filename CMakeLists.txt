cmake_minimum_required(VERSION 3.10)
project(Pong)

set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCES
    src/main.cpp
    src/application.cpp
    src/asset_manager.cpp
    src/game.cpp
    src/input.cpp
    src/physics.cpp
    src/renderer.cpp
    src/text.cpp
    third_party/tinyxml2/tinyxml2.cpp
)

# Include directories
include_directories(include/common)

if(APPLE)
    include_directories(include/mac)
elseif(WIN32)
    include_directories(include/windows)
endif()


# Add executable
add_executable(Pong ${SOURCES})

# Link SDL2 library
if(APPLE)
    # macOS specific libraries
    set(SDL2_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/mac/libSDL2-2.0.0.dylib")
    set(SDL2_IMG_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/mac/libSDL2_image-2.0.0.dylib")
    set(SDL2_TTF_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/mac/libSDL2_ttf-2.0.0.dylib")
elseif(WIN32)
    # Windows specific libraries
    set(SDL2_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/windows/SDL2.dll")
    set(SDL2_IMG_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/windows/SDL2_image.dll")
    set(SDL2_TTF_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/windows/SDL2_ttf.dll")
endif()

target_link_libraries(Pong
    ${SDL2_LIB_PATH}
    ${SDL2_IMG_LIB_PATH}
    ${SDL2_TTF_LIB_PATH}
)

# Copy .dylib file to the build directory

# might need to copy .dll files to build directory for windows
