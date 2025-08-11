# Create binancecpp library using new categorized structure
file(GLOB_RECURSE BINANCE_CPP_SOURCES
    "core/*.cpp"
    "financial_trading/*.cpp"
    "wallet_endpoints/*.cpp"
    "investment_service/*.cpp"
)

add_library(binancecpp SHARED
    binance_utils.cpp
    binance_logger.cpp
    binance_websocket.cpp
    ${BINANCE_CPP_SOURCES}
)

# Set target properties
set_target_properties(binancecpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    EXPORT_NAME binancecpp
)

# Link libraries
target_link_libraries(binancecpp
    PRIVATE
        JsonCpp::JsonCpp
        CURL::libcurl
        websockets
)

# Include directories
target_include_directories(binancecpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/.>
        $<INSTALL_INTERFACE:include/binancecpp>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Compiler-specific options for C++20
target_compile_options(binancecpp PRIVATE
    -fPIC
    $<$<CXX_COMPILER_ID:GNU>:-fconcepts>
    $<$<CXX_COMPILER_ID:Clang>:-fconcepts-ts>
)

# Add alias for consistent naming
add_library(binancecpp::binancecpp ALIAS binancecpp)