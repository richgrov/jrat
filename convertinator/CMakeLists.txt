add_executable(convertinator
    main.cpp
)

set_property(TARGET convertinator PROPERTY CXX_STANDARD 20)

target_link_libraries(convertinator common)
target_include_directories(convertinator PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(convertinator ${OpenCV_LIBS})
