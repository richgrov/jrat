add_executable(resizinator 
	main.cpp
	"test.h"
	test.cpp
)

target_include_directories(resizinator PRIVATE "../thirdparty/opencv/include")
target_link_libraries(resizinator common)
target_link_libraries(resizinator raylib)
target_link_directories(resizinator PRIVATE "../thirdparty/opencv/x64/vc16/lib")
target_link_libraries(resizinator opencv_world490d.lib)

