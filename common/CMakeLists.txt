add_library(common STATIC
    include/common/entrypoint.h
    include/common/image_to_byte.h
    include/common/stringutil.h
    include/common/supported_types.h
    include/common/textbox.h
    include/common/window.h
    src/entrypoint.cpp
    src/window.cpp
)

if (WIN32 AND (${CMAKE_BUILD_TYPE} STREQUAL "Release" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo"))
    target_compile_definitions(common PRIVATE JRAT_WINMAIN)
endif()

function(jrat_add_window_executable target_name)
    if (WIN32 AND (${CMAKE_BUILD_TYPE} STREQUAL "Release" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo"))
        message(STATUS "Building with console disabled because release mode is active")
        add_executable(${target_name} WIN32 ${ARGN})
    else()
        add_executable(${target_name} ${ARGN})
    endif()
endfunction()

set_property(TARGET common PROPERTY CXX_STANDARD 20)

target_include_directories(common PUBLIC include)
target_link_libraries(common raylib)
target_include_directories(common PUBLIC ../thirdparty/raygui/src)
target_include_directories(common PRIVATE resources)

target_include_directories(common PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(common ${OpenCV_LIBS})

target_compile_definitions(common PUBLIC _CRT_SECURE_NO_WARNINGS)

add_subdirectory(TESTING)
