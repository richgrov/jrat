jrat_add_window_executable(flipinator
    main.cpp
)

set_property(TARGET flipinator PROPERTY CXX_STANDARD 20)

target_link_libraries(flipinator common)
target_include_directories(flipinator PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(flipinator ${OpenCV_LIBS})
