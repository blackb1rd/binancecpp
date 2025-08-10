# Create binacpp library using modular structure only
file(GLOB_RECURSE BINANCE_CPP_SOURCES
    "initialization/*.cpp"
    "market_data/*.cpp"
    "account/*.cpp"
    "trading/*.cpp"
    "user_stream/*.cpp"
    "wallet/*.cpp"
    "utils/*.cpp"
)

add_library(binacpp SHARED
    binance.cpp
    binance_utils.cpp
    binance_logger.cpp
    binance_websocket.cpp
    ${BINANCE_CPP_SOURCES}
)

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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/.>
        $<INSTALL_INTERFACE:include/binacpp>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Compiler-specific options for C++20
target_compile_options(binacpp PRIVATE
    -fPIC
    $<$<CXX_COMPILER_ID:GNU>:-fconcepts>
    $<$<CXX_COMPILER_ID:Clang>:-fconcepts-ts>
)