set(SOURCE_FILES main.cpp)

jrat_add_window_executable(convertinator ${SOURCE_FILES})

set_property(TARGET convertinator PROPERTY CXX_STANDARD 20)

target_link_libraries(convertinator common)
target_include_directories(convertinator PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(convertinator ${OpenCV_LIBS})
