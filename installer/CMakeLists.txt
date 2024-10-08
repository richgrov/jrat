if (NOT MSVC)
    message(WARNING "MSVC is required for building the installer")
    return()
endif()

if (NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/res)
    message(WARNING "Not building installer because the res/ folder doesn't exist")
    return()
endif()

jrat_add_window_executable(installer
    main.cpp
    registry_key.cpp
    registry_key.h
    resources.cpp
    resources.h
    ui.cpp
    ui.h
    
    installer.manifest
    resources.rc
)

target_link_libraries(installer common)

set_property(TARGET installer PROPERTY CXX_STANDARD 20)

# In addition to requiring administrator mode in the installer.manifest, MSVC appears to link with
# default options that disable it. They need to be overriden here. Typically, target_link_options
# would be used, but that doesn't work for some reason. This is the older way that achieves the
# same result.
set_property(TARGET installer APPEND PROPERTY LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
