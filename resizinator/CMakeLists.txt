add_executable(resizinator 
	main.cpp
	resizinator.cpp 
	"resizinator.h"
	window_example.h
	"resize_ui.h"
	"resize_ui.cpp"
)

set_property(TARGET resizinator PROPERTY CXX_STANDARD 20)

target_include_directories(resizinator PRIVATE "../thirdparty/opencv/include")
target_link_libraries(resizinator common)
target_link_libraries(resizinator raylib)
target_link_directories(resizinator PRIVATE "../thirdparty/opencv/x64/vc16/lib")
target_include_directories(resizinator PRIVATE "../thirdparty/raygui/raygui/src")
# target_link_directories(resizinator PRIVATE "C:/PRO-100/jrat/thirdparty/raygui/raygui/src")
# target_link_directories(resizinator PRIVATE ${CMAKE_SOURCE_DIR}/thirdparty/raygui/raygui/src)
target_link_libraries(resizinator opencv_world490d.lib)
