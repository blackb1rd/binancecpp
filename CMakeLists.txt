cmake_minimum_required(VERSION 3.20)

project(binancecpp
    VERSION 1.0.0
    DESCRIPTION "C++ library for Binance API"
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
if(APPLE)
    set(CMAKE_INSTALL_RPATH "@loader_path/../lib")
elseif(WIN32)
    # On Windows, DLLs are found via PATH or same directory as executable
    set(CMAKE_INSTALL_RPATH "")
endif()

# Options
option(BINANCECPP_BUILD_EXAMPLES "Build examples" ON)
option(BINANCECPP_DEPLOY_MODE "Enable deployment mode, disables examples" OFF)

# Deployment mode overrides examples setting
if(BINANCECPP_DEPLOY_MODE)
    set(BINANCECPP_BUILD_EXAMPLES OFF CACHE BOOL "Deploy mode disables examples" FORCE)
endif()


# Find packages
find_package(jsoncpp CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(libwebsockets CONFIG REQUIRED)

# Add src/ as include directory for the entire project
include_directories(src)

# Add subdirectories
add_subdirectory(src)

# Conditionally build examples
if(BINANCECPP_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()


# Installation
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Install library
install(TARGETS binancecpp
    EXPORT binancecppTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(DIRECTORY src/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/binancecpp
    FILES_MATCHING PATTERN "*.h"
)

# Install examples if built and not in deploy mode
if(BINANCECPP_BUILD_EXAMPLES)
    # Example binaries are installed by the example/CMakeLists.txt
    message(STATUS "Example binaries will be installed to bin/examples")
endif()# Generate and install package config files
set(BINANCECPP_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/binancecpp)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/binancecppConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/binancecppConfig.cmake
    INSTALL_DESTINATION ${BINANCECPP_CMAKE_DIR}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/binancecppConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/binancecppConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/binancecppConfigVersion.cmake
    DESTINATION ${BINANCECPP_CMAKE_DIR}
)

install(EXPORT binancecppTargets
    FILE binancecppTargets.cmake
    NAMESPACE binancecpp::
    DESTINATION ${BINANCECPP_CMAKE_DIR}
)