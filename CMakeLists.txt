cmake_minimum_required(VERSION 3.8)
project(overseer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES overseer.cpp overseer.h utils.cpp utils.h main.cpp main.h)
add_executable(overseer ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")