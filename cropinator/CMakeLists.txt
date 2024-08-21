jrat_add_window_executable(cropinator
    main.cpp
)

set_property(TARGET cropinator PROPERTY CXX_STANDARD 20)

target_link_libraries(cropinator common)
target_include_directories(cropinator PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(cropinator ${OpenCV_LIBS})
