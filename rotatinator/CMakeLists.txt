add_executable(rotatinator
	main.cpp
	rotatinator.h
	rotatinator.cpp 
)

set_property(TARGET rotatinator PROPERTY CXX_STANDARD 20)

target_link_libraries(rotatinator common)
target_include_directories(rotatinator PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(rotatinator ${OpenCV_LIBS})