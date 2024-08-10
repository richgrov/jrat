add_library(common STATIC
    include/common/window.h
    src/window.cpp
    include/common/ui_framework.h
    src/ui_framework.cpp
    include/common/textbox.h
)

target_include_directories(common PUBLIC include)
target_link_libraries(common raylib)
target_include_directories(common PRIVATE ../thirdparty/raygui/raygui/src)