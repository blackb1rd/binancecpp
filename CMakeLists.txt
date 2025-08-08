cmake_minimum_required(VERSION 3.20)

project(binacpp
    VERSION 1.0.0
    DESCRIPTION "C++ library for Binance API"
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(jsoncpp CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(libwebsockets CONFIG REQUIRED)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(example)

# Add src/ as include directory for the entire project
include_directories(src)

# Installation
include(GNUInstallDirs)

install(TARGETS binacpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY src/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/binacpp
    FILES_MATCHING PATTERN "*.h"
)