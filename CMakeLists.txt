cmake_minimum_required(VERSION 3.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("jrat")

set(BUILD_SHARED_LIBS FALSE)

add_subdirectory(common)
add_subdirectory(demo)
add_subdirectory(resizinator)
