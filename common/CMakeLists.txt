add_library(common STATIC
    include/common/entrypoint.h
    include/common/image_to_byte.h
    include/common/stringutil.h
    include/common/supported_types.h
    include/common/textbox.h
    include/common/window.h
    src/window.cpp
)

target_include_directories(common PUBLIC include)
target_link_libraries(common raylib)
target_include_directories(common PRIVATE ../thirdparty/raygui/src)
target_include_directories(common PRIVATE resources)

target_include_directories(common PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(common ${OpenCV_LIBS})