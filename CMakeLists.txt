cmake_minimum_required(VERSION 3.7)
project(ssms)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c sqlite3.h sqlite3.c vec.h vec.c common.c common.h console.c console.h dataoperator.c dataoperator.h)
set(CMAKE_C_FLAGS "-fexec-charset=gbk")
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(ssms ${SOURCE_FILES})