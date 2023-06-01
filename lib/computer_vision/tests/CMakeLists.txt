add_executable(check_box_test src/test_check_person.cpp)
target_link_libraries(check_box_test computer_vision
                                 GTest::gtest_main)

add_test(check_box_test check_box_test)