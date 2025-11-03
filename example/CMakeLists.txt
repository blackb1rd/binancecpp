# Example executables
set(EXAMPLES
    example
    example_aggTrades
    example_depthCache
    example_klines
    example_template
    example_userStream
    example_wapi
)

foreach(EXAMPLE_NAME ${EXAMPLES})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_NAME}.cpp)
        add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)

        # Set C++20 standard for examples
        set_target_properties(${EXAMPLE_NAME} PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
        )

        target_link_libraries(${EXAMPLE_NAME}
            PRIVATE
                binancecpp::binancecpp
        )

        target_include_directories(${EXAMPLE_NAME}
            PRIVATE
                ${CMAKE_SOURCE_DIR}/src
        )

        # Set RPATH to find the library
        set_target_properties(${EXAMPLE_NAME} PROPERTIES
            INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
            BUILD_WITH_INSTALL_RPATH TRUE
        )

        # C++20 compile options
        target_compile_options(${EXAMPLE_NAME} PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:-fconcepts>
            $<$<CXX_COMPILER_ID:Clang>:-fconcepts-ts>
        )

        # On Windows, copy the DLL and its dependencies to the example executable directory
        if(WIN32)
            add_custom_command(TARGET ${EXAMPLE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    $<TARGET_FILE:binancecpp>
                    $<TARGET_FILE_DIR:${EXAMPLE_NAME}>
                COMMENT "Copying binancecpp.dll to example directory"
            )
            # Copy runtime DLLs for dependencies (JsonCpp, CURL, websockets)
            add_custom_command(TARGET ${EXAMPLE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    $<TARGET_RUNTIME_DLLS:${EXAMPLE_NAME}>
                    $<TARGET_FILE_DIR:${EXAMPLE_NAME}>
                COMMAND_EXPAND_LISTS
                COMMENT "Copying dependency DLLs to example directory"
            )
        endif()

        # Install example binaries
        install(TARGETS ${EXAMPLE_NAME}
            RUNTIME DESTINATION bin/examples
        )
    endif()
endforeach()
