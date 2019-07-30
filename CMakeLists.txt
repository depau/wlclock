cmake_minimum_required(VERSION 3.14)
project(wlclock)

set(CMAKE_CXX_STANDARD 14)

include(FindPkgConfig)
if(NOT PKG_CONFIG_FOUND)
    message(FATAL_ERROR "pkg-config not found!" )
endif()

pkg_check_modules(gtkmm-3.0 REQUIRED IMPORTED_TARGET gtkmm-3.0)

add_executable(wlclock
        clock.cc
        clock.h
        main.cc colors.h)

target_link_libraries(wlclock PkgConfig::gtkmm-3.0)