cmake_minimum_required(VERSION 3.12)
project(hse_oop_draw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sources
file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(draw ${SOURCES} main.cpp)

target_include_directories(draw PRIVATE include)
target_compile_definitions(draw PRIVATE NO_LEGACY_PPM)

if(MSVC)
    target_compile_options(draw PRIVATE /W4)
else()
    target_compile_options(draw PRIVATE -Wall -Wextra)
endif()

# Test tool: image diff
add_executable(imgdiff test/diff.cpp src/PngCodec.cpp)
target_include_directories(imgdiff PRIVATE include)

# Find zlib for PNG compression (optional)
find_package(ZLIB)
if(ZLIB_FOUND)
    target_link_libraries(draw PRIVATE ZLIB::ZLIB)
    target_link_libraries(imgdiff PRIVATE ZLIB::ZLIB)
    target_compile_definitions(draw PRIVATE HAVE_ZLIB)
    target_compile_definitions(imgdiff PRIVATE HAVE_ZLIB)
else()
    message(WARNING "Zlib not found. PNG compression will be disabled.")
    target_compile_definitions(draw PRIVATE NO_ZLIB)
    target_compile_definitions(imgdiff PRIVATE NO_ZLIB)
endif()
