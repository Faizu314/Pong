cmake_minimum_required(VERSION 3.10)
project(Pong)

set(CMAKE_CXX_STANDARD 17)

# Add source files
set(SOURCES
    src/main.cpp
    src/platform_utils.cpp
    src/application.cpp
    src/asset_manager.cpp
    src/game.cpp
    src/input.cpp
    src/physics.cpp
    src/renderer.cpp
    src/text.cpp
    third_party/tinyxml2/tinyxml2.cpp
)

# Add header files
set(HEADERS
    include/common/common.hpp
    include/common/defs.hpp
    include/common/structs.hpp
    include/common/platform_utils.hpp
    include/common/application.hpp
    include/common/asset_manager.hpp
    include/common/game.hpp
    include/common/input.hpp
    include/common/physics.hpp
    include/common/renderer.hpp
    include/common/text.hpp
    include/common/TinyXml/tinyxml2.h
)

# Organize headers and sources into folders for Visual Studio
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

# Include directories
include_directories(include/common)

if(APPLE)
    include_directories(include/mac)
elseif(WIN32)
    include_directories(include/windows)
endif()

# Add executable
if (APPLE)
    add_executable(Pong ${SOURCES} ${HEADERS})
elseif(WIN32)
    add_executable(Pong WIN32 ${SOURCES} ${HEADERS})
endif()

# Link SDL2, SDL2_image, and SDL2_ttf frameworks on macOS
if(APPLE)
    # Set the runtime path to include the location of the frameworks
    set_target_properties(Pong PROPERTIES
        INSTALL_RPATH "@loader_path"
        BUILD_WITH_INSTALL_RPATH TRUE
    )

    # Add the path to the frameworks
    set(CMAKE_FRAMEWORK_PATH "${CMAKE_SOURCE_DIR}/lib/mac")

    # Add the frameworks to the link process
    target_link_libraries(Pong
        "-F${CMAKE_SOURCE_DIR}/lib/mac"
        "-framework SDL2"
        "-framework SDL2_image"
        "-framework SDL2_ttf"
    )

    # Copy frameworks to the build directory
    add_custom_command(TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/lib/mac/SDL2.framework"
        "$<TARGET_FILE_DIR:Pong>/SDL2.framework"
    )
    add_custom_command(TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/lib/mac/SDL2_image.framework"
        "$<TARGET_FILE_DIR:Pong>/SDL2_image.framework"
    )
    add_custom_command(TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/lib/mac/SDL2_ttf.framework"
        "$<TARGET_FILE_DIR:Pong>/SDL2_ttf.framework"
    )
elseif(WIN32)
    # Windows specific libraries
    set(SDL2_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/windows/SDL2.lib")
    set(SDL2_IMG_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/windows/SDL2_image.lib")
    set(SDL2_TTF_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/windows/SDL2_ttf.lib")
    
    target_link_libraries(Pong
        ${SDL2_LIB_PATH}
        ${SDL2_IMG_LIB_PATH}
        ${SDL2_TTF_LIB_PATH}
    )

    # Copy SDL2.dll after build
    add_custom_command(TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/lib/windows/SDL2.dll"
            "$<TARGET_FILE_DIR:Pong>"
    )

    # Copy SDL2_image.dll after build
    add_custom_command(TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/lib/windows/SDL2_image.dll"
            "$<TARGET_FILE_DIR:Pong>"
    )

    # Copy SDL2_ttf.dll after build
    add_custom_command(TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/lib/windows/SDL2_ttf.dll"
            "$<TARGET_FILE_DIR:Pong>"
    )
endif()

# Copy and paste the assets in the executable directory
add_custom_command(TARGET Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:Pong>/Assets"
)
