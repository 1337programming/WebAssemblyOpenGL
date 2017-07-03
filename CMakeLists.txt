# This is only for compiling for native usage and test, not to be used to port WebAssembly
cmake_minimum_required(VERSION 3.0)
project(opie)

# GLFW Vendor
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(src/vendor/glfw)

# ASSIMP Vendor
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(src/vendor/assimp)

# Bullet
option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(src/vendor/bullet3)

# Platform check
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

## Include other vendors
include_directories(src/headers/
        src/vendor/assimp/include/
        src/vendor/bullet/src/
        src/vendor/glad/include/
        src/vendor/glfw/include/
        src/vendor/glm/
        src/vendor/stb/)

# Glob together files
file(GLOB VENDORS_SOURCES src/vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS src/headers/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB PROJECT_SHADERS src/shaders/*.comp
        src/shaders/*.frag
        src/shaders/*.geom
        src/shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
        Readme.md
        .gitattributes
        .gitignore
        .gitmodules)

# Include sources
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
        ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
        ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME} assimp glfw
        ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
        BulletDynamics BulletCollision LinearMath)
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

#
## Not sure if this is correct, but fixes c++ x64 arch issues with std
#set (CMAKE_CXX_STANDARD 11)
## includes cmake/FindSDL2.cmake
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#
#find_package (OpenGL REQUIRED)
## @TODO switch SDL to GLFW
#find_package(SDL2 REQUIRED)
#find_package(GLEW REQUIRED)
#include_directories(${SDL2_INCLUDE_DIR})
#include_directories(${OPENGL_INCLUDE_DIR})
#include_directories(${GLEW_INCLUDE_DIR})
#include_directories(deps/include)
#
#file(GLOB SOURCE_FILES src/*.cpp)
#
#add_executable(webassembly_opengl ${SOURCE_FILES} src/main.cpp)
#target_link_libraries(webassembly_opengl ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLM_LIBRARIES})
#target_compile_features(webassembly_opengl PRIVATE cxx_range_for)