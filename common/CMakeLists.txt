add_library(common STATIC
    include/common/entrypoint.h
    include/common/image_to_byte.h
    include/common/stringutil.h
    include/common/supported_types.h
    include/common/textbox.h
    include/common/window.h
    src/window.cpp
)

function(jrat_add_window_executable target_name files)
    if (WIN32 AND (${CMAKE_BUILD_TYPE} STREQUAL "Release" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo"))
        message(STATUS "Building with console disabled because release mode is active")
        add_executable(${target_name} WIN32 ${files})
        target_compile_definitions(${target_name} PRIVATE JRAT_WINMAIN)
    else()
        add_executable(${target_name} ${files})
    endif()
endfunction()

target_include_directories(common PUBLIC include)
target_link_libraries(common raylib)
target_include_directories(common PRIVATE ../thirdparty/raygui/src)
target_include_directories(common PRIVATE resources)

target_include_directories(common PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(common ${OpenCV_LIBS})