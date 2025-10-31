# CMakeLists.txt for tests directory
cmake_minimum_required(VERSION 3.20)

# Find required packages for tests
find_package(jsoncpp CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(libwebsockets CONFIG REQUIRED)

# Add src/ as include directory for tests
include_directories(../src)

# Get all test source files recursively
file(GLOB_RECURSE TEST_SOURCES "test_*.cpp")

# Create executable for each test file
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Get the filename without extension
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    # Get relative path for unique naming in case of conflicts
    file(RELATIVE_PATH REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${TEST_SOURCE})
    get_filename_component(REL_DIR ${REL_PATH} DIRECTORY)
    
    # Create unique test name by including directory path
    if(REL_DIR)
        string(REPLACE "/" "_" DIR_PREFIX ${REL_DIR})
        string(REPLACE "\\" "_" DIR_PREFIX ${DIR_PREFIX})
        set(UNIQUE_TEST_NAME ${DIR_PREFIX}_${TEST_NAME})
    else()
        set(UNIQUE_TEST_NAME ${TEST_NAME})
    endif()
    
    # Create executable
    add_executable(${UNIQUE_TEST_NAME} ${TEST_SOURCE})
    
    # Link against the main library and dependencies
    target_link_libraries(${UNIQUE_TEST_NAME} 
        binancecpp
        JsonCpp::JsonCpp
        CURL::libcurl
        $<IF:$<TARGET_EXISTS:websockets>,websockets,websockets_shared>
    )
    
    # Set C++ standard
    set_property(TARGET ${UNIQUE_TEST_NAME} PROPERTY CXX_STANDARD 20)
    set_property(TARGET ${UNIQUE_TEST_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
    
    # On Windows, copy the DLL and its dependencies to the test executable directory
    if(WIN32)
        add_custom_command(TARGET ${UNIQUE_TEST_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:binancecpp>
                $<TARGET_FILE_DIR:${UNIQUE_TEST_NAME}>
            COMMENT "Copying binancecpp.dll to test directory"
        )
        # Copy runtime DLLs for dependencies (JsonCpp, CURL, websockets)
        add_custom_command(TARGET ${UNIQUE_TEST_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:${UNIQUE_TEST_NAME}>
                $<TARGET_FILE_DIR:${UNIQUE_TEST_NAME}>
            COMMAND_EXPAND_LISTS
            COMMENT "Copying dependency DLLs to test directory"
        )
    endif()
    
    # Add to test suite (optional)
    # add_test(NAME ${UNIQUE_TEST_NAME} COMMAND ${UNIQUE_TEST_NAME})
endforeach()

# Create a convenience target to build all tests
add_custom_target(build_all_tests)
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    file(RELATIVE_PATH REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${TEST_SOURCE})
    get_filename_component(REL_DIR ${REL_PATH} DIRECTORY)
    
    if(REL_DIR)
        string(REPLACE "/" "_" DIR_PREFIX ${REL_DIR})
        string(REPLACE "\\" "_" DIR_PREFIX ${DIR_PREFIX})
        set(UNIQUE_TEST_NAME ${DIR_PREFIX}_${TEST_NAME})
    else()
        set(UNIQUE_TEST_NAME ${TEST_NAME})
    endif()
    
    add_dependencies(build_all_tests ${UNIQUE_TEST_NAME})
endforeach()

message(STATUS "Found ${CMAKE_CURRENT_SOURCE_DIR} test files")
message(STATUS "Test executables will be built for each test_*.cpp file")