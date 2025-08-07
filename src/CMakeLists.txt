# Create binacpp library - Option to use modular or single file approach
option(USE_MODULAR_STRUCTURE "Use modular file structure instead of single binacpp.cpp" OFF)

if(USE_MODULAR_STRUCTURE)
    # Modular structure - include all individual function files
    file(GLOB_RECURSE BINACPP_SOURCES
        "initialization/*.cpp"
        "market_data/*.cpp"
        "account/*.cpp"
        "trading/*.cpp"
        "user_stream/*.cpp"
        "wallet/*.cpp"
        "utils/*.cpp"
    )
    
    add_library(binacpp SHARED
        binacpp_modular.cpp
        binacpp_utils.cpp
        binacpp_logger.cpp
        binacpp_websocket.cpp
        ${BINACPP_SOURCES}
    )
else()
    # Traditional single file structure
    add_library(binacpp SHARED
        binacpp.cpp
        binacpp_utils.cpp
        binacpp_logger.cpp
        binacpp_websocket.cpp
    )
endif()

# Set target properties
set_target_properties(binacpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
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

# Compiler-specific options for C++20
target_compile_options(binacpp PRIVATE
    -fPIC
    $<$<CXX_COMPILER_ID:GNU>:-fconcepts>
    $<$<CXX_COMPILER_ID:Clang>:-fconcepts-ts>
)