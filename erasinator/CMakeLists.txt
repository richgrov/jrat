add_executable(erasinator
    main.cpp
)

set_property(TARGET erasinator PROPERTY CXX_STANDARD 20)

target_link_libraries(erasinator common)
target_include_directories(erasinator PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(erasinator ${OpenCV_LIBS})
