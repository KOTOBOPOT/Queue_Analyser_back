
add_executable(server_test
                    src/test_parse_query_string.cpp
                    src/test_error.cpp
                    src/test_types.cpp
                    src/test_generate_response.cpp
                )
target_link_libraries(server_test server GTest::gtest_main)
add_test(server_test server_test)