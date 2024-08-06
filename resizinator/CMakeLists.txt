add_executable(resizinator 
    main.cpp
)

 find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) # Not needed for CMake >= 2.8.11
target_link_libraries(resizinator ${OpenCV_LIBS})
#target_include_directories(resizinator PUBLIC "../thirdparty/opencv/include")
target_link_libraries(resizinator common)
#target_link_directories(resizinator PRIVATE "../thirdparty/opencv/x64/vc16/lib")
#target_link_libraries(resizinator opencv_world490d.lib)

