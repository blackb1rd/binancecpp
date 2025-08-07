# Create binacpp library
add_library(binacpp SHARED
    binacpp.cpp
    binacpp_utils.cpp
    binacpp_logger.cpp
    binacpp_websocket.cpp
)

# Set target properties
set_target_properties(binacpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Link libraries
target_link_libraries(binacpp 
    PRIVATE 
        JsonCpp::JsonCpp
        CURL::libcurl
        websockets
)

# Include directories
target_include_directories(binacpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/binacpp>
)

# Compiler-specific options
target_compile_options(binacpp PRIVATE -fPIC)