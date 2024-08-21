jrat_add_window_executable(resizinator 
    main.cpp
    resize_ui.h
    resize_ui.cpp
    resizinator.cpp 
    resizinator.h
)

set_property(TARGET resizinator PROPERTY CXX_STANDARD 20)

target_link_libraries(resizinator common)
target_link_libraries(resizinator raylib)
target_include_directories(resizinator PRIVATE "../thirdparty/raygui/src")

target_include_directories(resizinator PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(resizinator ${OpenCV_LIBS})
