cmake_minimum_required(VERSION 3.27)
project(myAllocator)

set(CMAKE_CXX_STANDARD 17)

# Specify the source files
set(SOURCES
        main.cpp
        MyAllocator.cpp
        MyAllocator.h
)

add_executable(myAllocator ${SOURCES})

add_executable(alloc_test TEST.cpp
                MyAllocator.cpp
                MyAllocator.h
)

# Optionally, add optimization flags for release mode
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Include current directory for headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
