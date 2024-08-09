add_executable(flipinator
	main.cpp
)

set_property(TARGET flipinator PROPERTY CXX_STANDARD 20)

target_include_directories(flipinator PRIVATE "../thirdparty/opencv/include")
target_link_libraries(flipinator common)
target_link_directories(flipinator PRIVATE "../thirdparty/opencv/x64/vc16/lib")
target_link_libraries(flipinator opencv_world490d.lib)