if (NOT MSVC)
    message(FATAL_ERROR "MSVC is required for building the installer")
endif()

add_executable(installer
    main.cpp
    installer.manifest
)

set_property(TARGET installer PROPERTY CXX_STANDARD 20)

# In addition to requiring administrator mode in the installer.manifest, MSVC appears to link with
# default options that disable it. They need to be overriden here. Typically, target_link_options
# would be used, but that doesn't work for some reason. This is the older way that achieves the
# same result.
set_property(TARGET installer APPEND PROPERTY LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
