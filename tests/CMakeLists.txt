# CMakeLists.txt for tests directory
cmake_minimum_required(VERSION 3.20)

# Find required packages for tests
find_package(jsoncpp CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(libwebsockets CONFIG REQUIRED)

# Add src/ as include directory for tests
include_directories(../src)

# Get all test source files
file(GLOB TEST_SOURCES "test_*.cpp")

# Create executable for each test file
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Get the filename without extension
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    # Create executable
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    
    # Link against the main library and dependencies
    target_link_libraries(${TEST_NAME} 
        binancecpp
        jsoncpp_lib
        CURL::libcurl
        websockets
    )
    
    # Set C++ standard
    set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 20)
    set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
    
    # Add to test suite (optional)
    # add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Create a convenience target to build all tests
add_custom_target(build_all_tests)
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_dependencies(build_all_tests ${TEST_NAME})
endforeach()

message(STATUS "Found ${CMAKE_CURRENT_SOURCE_DIR} test files")
message(STATUS "Test executables will be built for each test_*.cpp file")