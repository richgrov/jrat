set(SOURCE_FILES main.cpp)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    message(STATUS "Building with console disabled because release mode is active")
    add_executable(convertinator WIN32 ${SOURCE_FILES})
else()
    add_executable(convertinator ${SOURCE_FILES})
endif()

set_property(TARGET convertinator PROPERTY CXX_STANDARD 20)

target_link_libraries(convertinator common)
target_include_directories(convertinator PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(convertinator ${OpenCV_LIBS})
