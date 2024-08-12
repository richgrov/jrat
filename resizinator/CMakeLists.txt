add_executable(resizinator 
	main.cpp
	resizinator.cpp 
	"resizinator.h"
	window_example.h
	"resize_ui.h"
	"resize_ui.cpp"
)

set_property(TARGET resizinator PROPERTY CXX_STANDARD 20)

target_link_libraries(resizinator common)
target_link_libraries(resizinator raylib)
target_include_directories(resizinator PRIVATE "../thirdparty/raygui/src")

target_include_directories(resizinator PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(resizinator ${OpenCV_LIBS})
