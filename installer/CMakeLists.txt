if (NOT MSVC)
    message(FATAL_ERROR "MSVC is required for building the installer")
endif()

add_executable(installer main.cpp)
