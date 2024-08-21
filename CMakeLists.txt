cmake_minimum_required(VERSION 3.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("jrat")

set(BUILD_SHARED_LIBS FALSE)

find_package(OpenCV REQUIRED)
add_subdirectory(thirdparty/raylib)

add_subdirectory(common)
add_subdirectory(convertinator)
add_subdirectory(cropinator)
add_subdirectory(flipinator)
add_subdirectory(installer)
add_subdirectory(resizinator)
add_subdirectory(rotatinator) 
