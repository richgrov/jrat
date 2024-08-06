add_executable(resizinator 
	main.cpp
	"test.h"
	test.cpp
)

# target_include_directories(resizinator PRIVATE ../demo)

target_link_libraries(resizinator common)
target_link_libraries(resizinator raylib)