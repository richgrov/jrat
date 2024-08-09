add_executable(convertinator
	main.cpp
)

set_property(TARGET convertinator PROPERTY CXX_STANDARD 20)

target_include_directories(convertinator PRIVATE "../thirdparty/opencv/include")
target_link_libraries(convertinator common)
target_link_directories(convertinator PRIVATE "../thirdparty/opencv/x64/vc16/lib")
target_link_libraries(convertinator opencv_world490d.lib)