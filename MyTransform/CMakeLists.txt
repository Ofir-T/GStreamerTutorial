message("  mytransform/CMakeLists.txt:")
message ("  Making mytransform")

# Find GStreamer
find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0 gstreamer-base-1.0)

add_library (mytransform  SHARED EXCLUDE_FROM_ALL
        gstmytransform.c
)

#Package information
target_compile_definitions(mytransform PRIVATE
        PACKAGE_VERSION="1.0"
        GST_LICENSE="PUT LICENSE HERE"
        GST_PACKAGE_NAME="mytransform"
        GST_PACKAGE_ORIGIN="GiView Inc. 2024"
)

target_link_libraries(mytransform PRIVATE
        PkgConfig::gtk3
        PkgConfig::gstreamer
        PkgConfig::gstreamer-sdp
        PkgConfig::gstreamer-app
        PkgConfig::gstreamer-video
)

# Set properties for the plugin
set_target_properties(mytransform PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
        VERSION "${PROJECT_VERSION}"
        SOVERSION 1
)

get_target_property(libpath mytransform LIBRARY_OUTPUT_DIRECTORY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mytransform.pc.in ${CMAKE_BINARY_DIR}/mytransform.pc @ONLY)