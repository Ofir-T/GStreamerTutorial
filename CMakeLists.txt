cmake_minimum_required(VERSION 3.28)
project(GStreamerTutorial)

set(CMAKE_CXX_STANDARD 20)

#Packages
set(QT_VERSION "6.2.12")
set(QT_ARCHITECTURE "gcc_64")
set(QT_INSTALL_FOLDER "/home/$ENV{USER}/Qt/${QT_VERSION}/${QT_ARCHITECTURE}/lib/cmake")
set(CMAKE_PREFIX_PATH ${QT_INSTALL_FOLDER})  # this is critical for cmake to find qt modules. it is saved in cache, and deleted with it.

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS
        Widgets
        Qt6Charts
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
        Core
        Gui
        UiTools
        Widgets
        Charts
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(gtk3 REQUIRED IMPORTED_TARGET gtk+-3.0)
pkg_search_module(gstreamer REQUIRED IMPORTED_TARGET gstreamer-1.0>=1.4)
pkg_search_module(gstreamer-sdp REQUIRED IMPORTED_TARGET gstreamer-sdp-1.0>=1.4)
pkg_search_module(gstreamer-app REQUIRED IMPORTED_TARGET gstreamer-app-1.0>=1.4)
pkg_search_module(gstreamer-video REQUIRED IMPORTED_TARGET gstreamer-video-1.0>=1.4)

set( GST_PLUGIN_PATH ${CMAKE_CURRET_SOURCE_DIR}/cmake-build-debug/plugins)

add_subdirectory(MyTransform)

add_executable(my-gstreamer-app main.cpp)

target_link_libraries(my-gstreamer-app
        Qt::Core
        Qt::Gui
        Qt::UiTools
        Qt::Widgets
        Qt::Charts
        PkgConfig::gtk3
        PkgConfig::gstreamer
        PkgConfig::gstreamer-sdp
        PkgConfig::gstreamer-app
        PkgConfig::gstreamer-video
        mytransform
)