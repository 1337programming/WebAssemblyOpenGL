# This is only for compiling for native usage and test, not to be used to port WebAssembly
cmake_minimum_required(VERSION 2.8)
project(webassembly_opengl)

# Not sure if this is correct, but fixes c++ x64 arch issues with std
set (CMAKE_CXX_STANDARD 11)
# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package (OpenGL REQUIRED)
# @TODO switch SDL to GLFW
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(deps/include)

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(webassembly_opengl ${SOURCE_FILES})
target_link_libraries(webassembly_opengl ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLM_LIBRARIES})
target_compile_features(webassembly_opengl PRIVATE cxx_range_for)