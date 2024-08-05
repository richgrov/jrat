add_library(common
    include/common.h
    main.cpp
)

target_include_directories(common PUBLIC include)
