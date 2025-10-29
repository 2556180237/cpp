cmake_minimum_required(VERSION 3.12)
project(hse_oop_draw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Источники
file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(draw ${SOURCES})

target_include_directories(draw PRIVATE include)

if(MSVC)
    target_compile_options(draw PRIVATE /W4)
else()
    target_compile_options(draw PRIVATE -Wall -Wextra)
endif()
