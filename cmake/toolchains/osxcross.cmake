set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Requires osxcross installed and OSXCROSS_ROOT exported
if(NOT DEFINED ENV{OSXCROSS_ROOT})
  message(FATAL_ERROR "OSXCROSS_ROOT is not set. Please export OSXCROSS_ROOT to your osxcross root")
endif()

# Compilers from osxcross (GCC-based osxcross)
set(CMAKE_C_COMPILER $ENV{OSXCROSS_ROOT}/target/bin/o64-gcc)
set(CMAKE_CXX_COMPILER $ENV{OSXCROSS_ROOT}/target/bin/o64-g++)

if(NOT EXISTS ${CMAKE_C_COMPILER} OR NOT EXISTS ${CMAKE_CXX_COMPILER})
  message(FATAL_ERROR "o64-gcc / o64-g++ not found in $ENV{OSXCROSS_ROOT}/target/bin")
endif()

# SDK (can be provided via SDKROOT)
if(DEFINED ENV{SDKROOT})
  set(CMAKE_OSX_SYSROOT $ENV{SDKROOT})
endif()

set(CMAKE_FIND_ROOT_PATH $ENV{OSXCROSS_ROOT}/target/SDK)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)



