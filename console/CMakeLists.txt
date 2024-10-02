cmake_minimum_required(VERSION 3.10)
# Set the compiling mode flags

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -s")

# Set the project name
project(Console)

# Add the executable
add_executable(console
src/main.c)