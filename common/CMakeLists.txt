add_library(common STATIC
    include/common.h
    src/main.cpp
)

target_include_directories(common PUBLIC include)
